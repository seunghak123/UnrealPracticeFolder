using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using Newtonsoft.Json;
using OfficeOpenXml;
using System.Threading.Tasks;
using System.Reflection;

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
        //C++ SerealizeField Class 
        static void MakeCPPClassFile(string fileName, Dictionary<string, string> fileValues)
        {
            if (Directory.Exists(outputScriptPath) == false)
            {
                Directory.CreateDirectory(outputScriptPath);
            }

            if (outputScriptPath.Last() != '/' || outputScriptPath.Last() != '\\')
            {
                outputScriptPath.Append('/');
            }

            string makedFile = $"{outputScriptPath}/{fileName}.cpp";
            string className = UpperCaseFirstLetter(fileName);
            string insertText = "USTRUCT(BlueprintType)\n";
            insertText += $"struct F{className}Data\n" + '{';
            insertText += "\n\tGENERATED_BODY()\n";
            insertText += "public: ";
            for (int i = 0; i < fileValues.Count; i++)
            {
                insertText += "\n\tUPROPERTY(EditAnwhere, BlueprintReadOnly, Category= FurnitureData)";
                insertText += $"\n\t{fileValues.ElementAt(i).Value} {fileValues.ElementAt(i).Key};\n";
            }
            insertText += "\n}";

            File.WriteAllText(makedFile, insertText);
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