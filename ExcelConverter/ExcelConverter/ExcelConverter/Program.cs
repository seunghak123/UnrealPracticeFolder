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
        //Json Output Path
        static string outputJsonPath = "./JsonFiles";
        //Cs 또는 Cpp Output Path
        static string outputScriptPath = "./Script";

        static void Main(string[] argus)
        {
            ExcelPackage.LicenseContext = LicenseContext.Commercial;
            #region TestCode
            //Excel Input Path
            string inputPath = "./ExcelFiles";
            #endregion
            //if (argus.Length <= 0)
            //{
            //    Console.WriteLine("Error Need Excel, Json folder Path");
            //    return;
            //}
            ////Excel Input Path
            //string inputPath = argus[0];
            ////Json Output Path
            //string outputJsonPath = argus[1];
            ////Cs 또는 Cpp Output Path
            //string outputScriptPath = argus[2];
            Console.WriteLine($"엑셀 Input 경로 : {inputPath}");
            //Console.WriteLine($"Json Output 경로 : {outputJsonPath}");
            //Console.WriteLine($"Class Output 경로 : {outputScriptPath}");

            string[] excelfileArrays = GetFileLists(inputPath);
            Console.WriteLine("엑셀  갯수" + excelfileArrays.Length);
            for(int i=0;i < excelfileArrays.Length; i++)
            {
               // Task task1 = Task.Run(() =>
               //{
                   ReadExcelFile(excelfileArrays[i]); 
                //});
            }
            //특정 경로에서 엑셀리스트 받기
            //해당 엑셀의 워크 시트를 딴 json파일 생성및 class파일 생성(cs파일) 

            //List<Dictionary<string, object>> excelData = ReadExcelFile(excelfileArrays[0]);

            //if (excelData != null)
            //{
            //    string jsonData = JsonConvert.SerializeObject(excelData, Formatting.Indented);
            //    File.WriteAllText(jsonFilePath, jsonData);

            //    Console.WriteLine("Excel data has been converted to JSON successfully.");
            //}
            //else
            //{
            //    Console.WriteLine("Failed to read Excel data.");
            //}
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
                        classResult.Add(header, worksheet.Cells[2, col].Value?.ToString());
                    }
                    //result.Add(rowData);

                    MakeClassFile(worksheet.Name, classResult);
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

            string makedFile = $"{outputScriptPath}{fileName}";
            string className = UpperCaseFirstLetter(fileName);
            string insertText = "USTRUCT(BlueprintType)\n";
            insertText += $"struct F{className}Data\n" + '{';
            insertText += "GENERATED_BODY()\n";
            insertText += "public: ";
            for (int i = 0; i < fileValues.Count; i++)
            {
                insertText += "\nUPROPERTY(EditAnwhere, BlueprintReadOnly, Category= FurnitureData)";
                insertText += $"\n{fileValues.ElementAt(i).Value} {fileValues.ElementAt(i).Key}";
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