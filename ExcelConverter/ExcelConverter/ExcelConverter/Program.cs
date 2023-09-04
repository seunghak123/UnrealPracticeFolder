using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using Newtonsoft.Json;
using OfficeOpenXml;
using System.Threading.Tasks;
using System.Reflection;
using static System.Runtime.InteropServices.JavaScript.JSType;
using System.Text.Json.Nodes;

namespace ExcelToJsonConverter
{
    class Program
    {
        /// <summary>
        /// 엑셀 파일 읽고, Json및 cs파일로 저장하는 쓰레드
        /// </summary>
        // Task task1 = Task.Run(() =>
        //{
        //    //작업 수행
        //});
        //Excel Input Path
        string inputPath = "./ExcelFiles";
        //Json Output Path
        static string outputJsonPath = "./JsonFiles";
        //Cs 또는 Cpp Output Path
        static string outputScriptPath = "./Script";
        static int isCsharpProject = 1;
        static void Main(string[] argus)
        {
            ExcelPackage.LicenseContext = LicenseContext.Commercial;
            #region TestCode
            //Excel Input Path
            string inputPath = "./ExcelFiles";
            #endregion
  
            if(argus.Length > 0)
            {
                ////Excel Input Path
                inputPath = argus[0];
                ////Json Output Path
                outputJsonPath = argus[1];
                ////Cs 또는 Cpp Output Path
                outputScriptPath = argus[2];
                ///Cs인지 Cpp인지 선택하는 인자
                isCsharpProject = int.Parse(argus[3]);
            }
            Console.WriteLine($"엑셀 Input 경로 : {inputPath}");
            //Console.WriteLine($"Json Output 경로 : {outputJsonPath}");
            //Console.WriteLine($"Class Output 경로 : {outputScriptPath}");

            string[] excelfileArrays = GetFileLists(inputPath);
            Console.WriteLine("엑셀  갯수" + excelfileArrays.Length);
            List<Task> excelTask = new List<Task>();
            for(int i=0;i < excelfileArrays.Length; i++)
            {
                int index = i;
                excelTask.Add(Task.Run(() =>
                {
                   ReadExcelFile(excelfileArrays[index]); 
                }));
            }
            
            foreach(var autoTask in excelTask)
            {
                autoTask.Wait();
            }
        }

        static void ReadExcelFile(string excelPath)
        {
            List<string> headerFileLists = new List<string>();
            using (var package = new ExcelPackage(new FileInfo(excelPath)))
            {
                for(int i=0;i < package.Workbook.Worksheets.Count; i++)
                {
                    var classResult = new Dictionary<string, string>();
                    var result = new List<Dictionary<string, object>>();
                    ExcelWorksheet worksheet = package.Workbook.Worksheets[i];
                    for (int row = 3; row <= worksheet.Dimension.Rows; row++)
                    { // Assuming header is in the first row
                        Dictionary<string, object> rowData = new Dictionary<string, object>();

                        for (int col = 1; col <= worksheet.Dimension.Columns; col++)
                        {
                            //변수명
                            string header = worksheet.Cells[1, col].Value?.ToString();
                            if (header==null || header.Contains("#"))
                            {
                                continue;
                            }
                            object cellValue = worksheet.Cells[row, col].Value;
                            Type type = GetTypeFromString(worksheet.Cells[2, col].Value?.ToString());

                            switch (type){
                                case Type intType when intType == typeof(int):
                                    if (int.TryParse(cellValue.ToString(), out int intValue))
                                        rowData[header] = intValue;
                                    else
                                        rowData[header] = cellValue;
                                    break;

                                case Type doubleType when doubleType == typeof(double):
                                    if (double.TryParse(cellValue.ToString(), out double doubleValue))
                                        rowData[header] = doubleValue;
                                    else
                                        rowData[header] = cellValue;
                                    break;

                                case Type stringType when stringType == typeof(string):
                                    rowData[header] = cellValue;
                                    break;
                                case Type stringType when stringType == typeof(DateTime):
                                    rowData[header] = cellValue;
                                    break;
                                default:
                                    rowData[header] = cellValue;
                                    break;
                            }
                        }
                        result.Add(rowData);
                    }

                    MakeJsonFile(worksheet.Name, result);
                    for (int col = 1; col <= worksheet.Dimension.Columns; col++)
                    {
                        string header = worksheet.Cells[1, col].Value?.ToString();
                        if (header == null || header.Contains("#"))
                        {
                            continue;
                        }
                        classResult.Add(header, worksheet.Cells[2, col].Value?.ToString());
                    }
                    if (isCsharpProject == 1)
                    {
                        MakeClassFile(worksheet.Name, classResult);
                    }
                    else
                    {
                        headerFileLists.Add(worksheet.Name);
                        MakeCPPClassFile(worksheet.Name, classResult);
                    }
                }
                //Make Class
            }
        }
        //C# SerealizeField Class 
        static void MakeClassFile(string fileName, Dictionary<string, string> fileValues)
        {
            if (Directory.Exists(outputScriptPath) == false)
            {
                Directory.CreateDirectory(outputScriptPath);
            }
 
            string className = UpperCaseFirstLetter(fileName);
            string makedFile = $"{outputScriptPath}/J{className}Data.cs";
            string insertText = "[System.Serializable]\n";
            insertText += $"public class J{className}Data\n" + '{';
            for(int i = 0; i < fileValues.Count; i++)
            {
                insertText += $"\n\tpublic {fileValues.ElementAt(i).Value} {fileValues.ElementAt(i).Key};";
            }
            insertText += "\n}";
            File.WriteAllText(makedFile, insertText);
        }
        static void MakeJsonFile(string fileName, List<Dictionary<string, object>> fileValues)
        {
            if (Directory.Exists(outputJsonPath) == false)
            {
                Directory.CreateDirectory(outputJsonPath);
            }

            string className = UpperCaseFirstLetter(fileName);
            string makedFile = $"{outputJsonPath}/J{className}.json";

            string jsonData = JsonConvert.SerializeObject(fileValues, Formatting.Indented);
            File.WriteAllText(makedFile, jsonData);
        }
        static void MakeCppIncludeHeaderFile(List<string> headerLists)
        {
            string makedFile = $"{outputScriptPath}/Header/FBaseDataLists.h";
            string insertText = "#pragma once\n";
            insertText += $"\n#include \"FBaseData.h\"";
            foreach (string headerFiles in headerLists)
            {
                insertText += $"\n#include \"F{headerFiles}Data.h\"";
            }
            //파일리스트 include된 내용 추가

            File.WriteAllText(makedFile, insertText);
        }
        static void MakeDefaultCppClassFile()
        {
            string makedFile = $"{outputScriptPath}/Class/FBaseData.h";
            string insertText = "#pragma once\nUCLASS()\n";
            insertText += "template <typename T>";
            insertText += $"struct FBaseData  \n" + '{';
            insertText += "\n\tGENERATED_BODY()\n";
            insertText += "public: ";
            insertText += "\n\t virtual T ReadJsonData()";
            insertText += "\n\t virtual TArray<T> ReadJsonDatas()";
            insertText += "\n}";
        }
        //C++ SerealizeField Class 
        static void MakeCPPClassFile(string fileName, Dictionary<string, string> fileValues)
        {
            if (Directory.Exists(outputScriptPath) == false)
            {
                Directory.CreateDirectory(outputScriptPath);
            }
            MakeDefaultCppClassFile();

            //Cpp 파일 생성
            if (outputScriptPath.Last() != '/' || outputScriptPath.Last() != '\\')
            {
                outputScriptPath.Append('/');
            }

            string makedFile = $"{outputScriptPath}/Class/F{fileName}.cpp";
            //헤더파일 추가
            string insertText = $"#include \"F{fileName}.h\"";
            insertText += $"F{fileName} F{fileName}::ReadJsonDatas()\n" + '{';
            insertText += $"F{fileName} returnValue = new F{fileName}()";
            for (int i = 0; i < fileValues.Count; i++)
            {
                string ValueType = ReturnSaveTextType(fileValues.ElementAt(i).Value);
                if(ValueType == "FString")
                {
                    ValueType = "FString()";
                } 
                insertText += $"returnValue.{fileValues.ElementAt(i).Key} = ReadJsonValue(JsonObject, TEXT(\"{fileValues.ElementAt(i).Key}\"),{ValueType})";
            }

            insertText += "\n}";


            //밑의 주석들은 혹시 몰라 남겨놓은 코드 
            //string className = UpperCaseFirstLetter(fileName);
            //string insertText = "USTRUCT(BlueprintType)\n";
            //insertText += $"struct F{className}Data\n" + '{';
            //insertText += "\n\tGENERATED_BODY()\n";
            //insertText += "public: ";
            //for (int i = 0; i < fileValues.Count; i++)
            //{
            //    string ValueType = ReturnSaveTextType(fileValues.ElementAt(i).Value);
            //    insertText += "\n\tUPROPERTY(EditAnwhere, BlueprintReadOnly, Category= FurnitureData)";
            //    insertText += $"\n\t{ValueType} {fileValues.ElementAt(i).Key};\n";
            //}
            //insertText += "\n}";

            File.WriteAllText(makedFile, insertText);

            //header 파일 생성

            string makedHeaderFile = $"{outputScriptPath}/Header/F{fileName}.h";
            string headerInsertText = "#pragma once\nUCLASS()\n";
            headerInsertText += $"class  F{fileName}Data : public FBaseData \n" + '{';
            headerInsertText += "\n\tGENERATED_BODY()\n";
            headerInsertText += "public: ";
            for (int i = 0; i < fileValues.Count; i++)
            {
                string ValueType = ReturnSaveTextType(fileValues.ElementAt(i).Value);
                headerInsertText += "\n\tUPROPERTY(EditAnwhere, BlueprintReadOnly, Category= FurnitureData)";
                //여기에 Fstring 일경우에 Value 값을 Fstring으로 나와야한다.
                headerInsertText += $"\n\t{ValueType} {fileValues.ElementAt(i).Key};\n";
            }
            headerInsertText += "\n}";


        }
        public static string ReturnSaveTextType(string typeString)
        {
            //해당 함수는 C++ 즉 언리얼일때만 실행한다.
            string returnTypeString = null;
            switch (typeString)
            {
                case "string":
                    returnTypeString = "FString";
                    break;
                default:
                    returnTypeString = typeString;
                    break;
            }
            return returnTypeString;
        }
        public static string UpperCaseFirstLetter(string input)
        {
            if (string.IsNullOrEmpty(input))
            {
                return input;
            }

            char[] charArray = input.ToCharArray();
            charArray[0] = char.ToUpper(charArray[0]);
            return new string(charArray);
        }
        public static Type GetTypeFromString(string typeString)
        {
            Type returnType = typeof(int);
            string lowcaseType = typeString.ToLower();
            switch (typeString)
            {
                case "int":
                case "integer":
                case "Int":
                    //int값
                    returnType = typeof(int);
                    break;
                case "char":
                case "character":
                    returnType = typeof(char);
                    break;
                case "datetime":
                case "time":
                    returnType = typeof(DateTime);
                    break;
                case "float":
                case "double":
                    returnType = typeof(float);
                    break;
                case "string":
                    returnType = typeof(string);
                    break;
            }
            return returnType;
        }
        public static string[] GetFileLists(string path)
        {
            // 대상 폴더 경로

            string folderPath = path;
            string[] files = null;

            if (Directory.Exists(folderPath) == false)
            {
                Directory.CreateDirectory(folderPath);
            }

            files = Directory.GetFiles(folderPath);
            // 폴더 내 파일 목록 가져오기

            Console.WriteLine("Read All Excel Files");
            return files;
        }
    }
}