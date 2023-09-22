using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using Newtonsoft.Json;
using OfficeOpenXml;
using System.Threading.Tasks;
using System.Reflection;
using System.Reflection.PortableExecutable;
using System.Data;
using Newtonsoft.Json.Linq;

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
                            if (isCsharpProject == 0 && header == "index")
                            {
                                header = "Name";
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
                                    if (isCsharpProject == 0)
                                    {
                                        switch (type)
                                        {
                                            case Type intarrayType when intarrayType == typeof(int[]):
                                            case Type douarrayType when douarrayType == typeof(double[]):
                                            case Type floarrayType when floarrayType == typeof(float[]):
                                            case Type strarrayType when strarrayType == typeof(string[]):
                                                rowData[header] = JArray.Parse($"[{cellValue.ToString()}]");
                                                break;
                                        }
                                    }
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
                        MakeDataTableCPPClassFile(worksheet.Name, classResult);
                    }
                }
                //Make Class
            }
            if (isCsharpProject == 0)
            {
                MakeDataTableCppIncludeHeaderFile(headerFileLists);
            }
        }
        public static string ReplaceFirst(string s, char re, char ch,int index)
        {
            int offsetIndex = index;
            string first = s.Substring(0, s.IndexOf(re));
            char midle = ch;
            string last = s.Substring(s.IndexOf(re) + re, s.Length - offsetIndex);
            return string.Concat(first, midle, last);
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

            string className = UpperCaseFirstLetter(fileName).ToLower();
            string makedFile = $"{outputJsonPath}/j{className}.json";

            string jsonData = JsonConvert.SerializeObject(fileValues, Formatting.Indented);

            File.WriteAllText(makedFile, jsonData);
        }
        #region 언리얼 소켓용 클래스 생성
        static void MakeSocketCppIncludeHeaderFile(List<string> headerLists)
        {
            string makedFilePath = $"{outputScriptPath}/Header";

            if (Directory.Exists(makedFilePath) == false)
            {
                Directory.CreateDirectory(makedFilePath);
            }

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
        static void MakeSocketDefaultCppClassFile()
        {
            string makedFilePath = $"{outputScriptPath}/Header";

            if (Directory.Exists(makedFilePath) == false)
            {
                Directory.CreateDirectory(makedFilePath);
            }

            string makedFile = $"{outputScriptPath}/Header/FBaseData.h";
            string insertText = "#pragma once\n";
            insertText += "#include \"EngineMinimal.h\"\n";
            insertText += "#include \"CoreMinimal.h\"\n";
            insertText += "#include \"FBaseData.generated.h\"\n";
            insertText += "UCLASS()\n";
  
            insertText += $"class FBaseData : public UObject \n" + '{';
            insertText += "\n\tGENERATED_BODY()\n";
            insertText += "public: ";
            insertText += "\n\ttemplate <typename T>";
            insertText += "\n\tstatic T ReadJsonData();";
            insertText += "\n\ttemplate <typename T>";
            insertText += "\n\tstatic TArray<T> ReadJsonDatas();";
            insertText += "\n};";
            File.WriteAllText(makedFile, insertText);
        }
        //C++ SerealizeField Class 
        static void MakeSocketCPPClassFile(string fileName, Dictionary<string, string> fileValues)
        {
            if (Directory.Exists(outputScriptPath) == false)
            {
                Directory.CreateDirectory(outputScriptPath);
            }
            MakeSocketDefaultCppClassFile();
            //Cpp 파일 생성
            if (outputScriptPath.Last() != '/' || outputScriptPath.Last() != '\\')
            {
                outputScriptPath.Append('/');
            }

            string makedFile = $"{outputScriptPath}/Class/F{fileName}Data.cpp";
            string insertText = $"#include \"F{fileName}Data.h\"\n\n";


            insertText += $"F{fileName}Data F{fileName}Data::ReadJsonData()\n" + '{' + '\n';
            insertText += $"\tTArray<TSharedPtr<FJsonValue>> objArray = JsonObject->GetArrayField(TEXT(\"F{fileName}Data\"));\n";
            insertText += $"\tF{fileName}Data returnValue = new F{fileName}Data();\n";
            for (int i = 0; i < fileValues.Count; i++)
            {
                string ValueType = ReturnSaveTextType(fileValues.ElementAt(i).Value);
                if(ValueType == "FString")
                {
                    ValueType = "FString()";
                } 
                insertText += $"\treturnValue.{fileValues.ElementAt(i).Key} = ReadJsonValue(JsonObject, TEXT(\"{fileValues.ElementAt(i).Key}\"),{ValueType});\n";
            }
            insertText += "\n}";

            insertText += $"\nTArray<F{fileName}Data> F{fileName}Data::ReadJsonDatas()\n" + '{' + '\n';
            insertText += $"\tTArray<F{fileName}Data> returnValues = new TArray<F{fileName}Data>();\n";
            for (int i = 0; i < fileValues.Count; i++)
            {

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
            //    insertText += "\n\tUPROPERTY(EditAnywhere, BlueprintReadOnly, Category= FurnitureData)";
            //    insertText += $"\n\t{ValueType} {fileValues.ElementAt(i).Key};\n";
            //}
            //insertText += "\n}";

            File.WriteAllText(makedFile, insertText);

            //header 파일 생성
            string heaperPath = $"{outputScriptPath}/Header";
            if (Directory.Exists(heaperPath) == false)
            {
                Directory.CreateDirectory(heaperPath);
              }
            string makedHeaderFile = $"{outputScriptPath}/Header/F{fileName}Data.h";
            string headerInsertText = "#pragma once\nUSTRUCT()\n";
            headerInsertText += $"#include \"FBaseData.h\"\n";
            headerInsertText += $"#include \"F{fileName}Data.generated.h\"\n";
            headerInsertText += $"struct  F{fileName}Data : public FBaseData \n" + '{';
            headerInsertText += "\n\tGENERATED_BODY()\n";
            headerInsertText += "public: ";
            for (int i = 0; i < fileValues.Count; i++)
            {
                string ValueType = ReturnSaveTextType(fileValues.ElementAt(i).Value);
                headerInsertText += "\n\tUPROPERTY(EditAnywhere, BlueprintReadOnly, Category= FurnitureData)";
                //여기에 Fstring 일경우에 Value 값을 Fstring으로 나와야한다.
                headerInsertText += $"\n\t{ValueType} {fileValues.ElementAt(i).Key};\n";
            }
            headerInsertText += "public: \n";
            headerInsertText += $"\tF{fileName}Data ReadJsonData();\n";
            headerInsertText += $"\tTArray<F{fileName}Data> ReadJsonDatas();\n";
            headerInsertText += "\n};";

            File.WriteAllText(makedHeaderFile, headerInsertText);
        }
        #endregion
        #region 언리얼 데이터 테이블 클래스 생성
        static void MakeDataTableCppIncludeHeaderFile(List<string> headerLists)
        {
            string makedFilePath = $"{outputScriptPath}/Header";

            if (Directory.Exists(makedFilePath) == false)
            {
                Directory.CreateDirectory(makedFilePath);
            }

            string makedFile = $"{outputScriptPath}/Header/FBaseDataLists.h";

            string insertText = "#pragma once\n";
            insertText += $"\n#include \"FBaseData.h\"";
            foreach (string headerFiles in headerLists)
            {
                insertText += $"\n#include \"U{headerFiles}Data.h\"";
            }
            //파일리스트 include된 내용 추가

            File.WriteAllText(makedFile, insertText);
        }
        static void MakeDataTableDefaultCppHeaderFile()
        {
            string makedFilePath = $"{outputScriptPath}/Header";

            if (Directory.Exists(makedFilePath) == false)
            {
                Directory.CreateDirectory(makedFilePath);
            }

            string makedFile = $"{outputScriptPath}/Header/FBaseData.h";
            string insertText = "#pragma once\n";
            insertText += "#include \"EngineMinimal.h\"\n";
            insertText += "#include \"CoreMinimal.h\"\n";
            insertText += "#include \"Engine\\DataTable.h\"\n";
            insertText += "#include \"FBaseData.generated.h\"\n\n";
            
            insertText += "USTRUCT(Atomic,BlueprintType)\n";
            insertText += $"struct FBaseData : public FTableRowBase \n" + '{';
            insertText += "\n\tGENERATED_BODY()\n";
            insertText += "\n};";
            //insertText += "\n\n";
            //insertText += "UCLASS()\n";
            //insertText += "class UBaseTable : public UDataTable\n" + '{';
            //insertText += "\n\tGENERATED_BODY()\n";
            //insertText += "}";

            File.WriteAllText(makedFile, insertText);
        }
        static void MakeDataTableCPPClassFile(string fileName, Dictionary<string, string> fileValues)
        {
            MakeDataTableDefaultCppHeaderFile();
            MakeDataTableCPPClassHeaderFile(fileName, fileValues);
            MakeUnrealTableLoader();
        }
        static void MakeDataTableCPPClassHeaderFile(string fileName, Dictionary<string, string> fileValues)
        {
            //header 파일 생성
            string heaperPath = $"{outputScriptPath}/Header";
            if (Directory.Exists(heaperPath) == false)
            {
                Directory.CreateDirectory(heaperPath);
            }
            string makedHeaderFile = $"{outputScriptPath}/Header/F{fileName}Data.h";
            string headerInsertText = "#pragma once\n";
            headerInsertText += "#include \"CoreMinimal.h\"\n";
            headerInsertText += $"#include \"FBaseData.h\"\n";
            headerInsertText += $"#include \"F{fileName}Data.generated.h\"\n";
            headerInsertText += "USTRUCT(Atomic, BlueprintType)\n";
            headerInsertText += $"\nstruct  F{fileName}Data : public FBaseData \n" + '{';
            headerInsertText += "\n\tGENERATED_BODY()\n";
            headerInsertText += "public: ";
            for (int i = 0; i < fileValues.Count; i++)
            {
                string ValueType = ReturnSaveTextType(fileValues.ElementAt(i).Value);
                if(fileValues.ElementAt(i).Key == "index")
                {
                    continue;
                }
                headerInsertText += $"\n\tUPROPERTY(EditAnywhere, BlueprintReadWrite, Category= \"{fileName}Data\")";
                //여기에 Fstring 일경우에 Value 값을 Fstring으로 나와야한다.
                headerInsertText += $"\n\t{ValueType} {fileValues.ElementAt(i).Key};\n";
            }
            headerInsertText += "\n};";

            File.WriteAllText(makedHeaderFile, headerInsertText);
        }
        static void MakeUnrealTableLoader()
        {
            string makedFilePath = $"{outputScriptPath}/Header";

            if (Directory.Exists(makedFilePath) == false)
            {
                Directory.CreateDirectory(makedFilePath);
            }
            string makedFile = $"{outputScriptPath}/Header/JsonDataSubSystem.h";
            string insertText = "#pragma once\n";
            insertText += "#include \"CoreMinimal.h\"\n";
            insertText += "#include \"Subsystems/GameInstanceSubsystem.h\"\n";
            insertText += "#include \"JsonDataSubsystem.generated.h\"\n";
            insertText += "#include \"JsonDataSubsystem.generated.h\"\n";
            insertText += "\nUCLASS()\n";
            insertText += "class UJsonDataSubsystem : public UGameInstanceSubsystem\n" + "{\n";
            insertText += "\tGENERATED_BODY()\n";
            insertText += "public:\n";
            insertText += "\tstatic UJsonDataSubsystem* jsonDataSubSystem;\n";
            insertText += "public:\n";
            insertText += "\tvoid Initialize(FSubSystemCollectionBase& Collection) override;\n";
            insertText += "\tvoid Deinitialize() override\n";
            insertText += "\tstatic UJsonDataSubSystem* GetInst();\n";
            insertText += "public:\n";
            insertText += "\ttemplate <typename T>\n";
            insertText += "\tstatic TArray<T*> LoadJsonData(FString filePath)\n" + "\t{\n";
            insertText += "\t\tTArray<T*> dataArrays = nullptr;\n";
            insertText += "\t\tUDataTable* userDataTable = LoadObject<UDataTable>(nullptr,*filePath);\n";
            insertText += "\t\tif(IsValid(userDataTable))\n";
            insertText += "\t\t{\n";
            insertText += "\t\t\tuserDataTable->GetAllRows<T>(nullptr,dataArrays);\n";
            insertText += "\t\t}\n";
            insertText += "\n\t\treturn dataArrays;";
            insertText += "\n\t}";
            insertText += "\n};";
            File.WriteAllText(makedFile, insertText);

            string makedcppFile = $"{outputScriptPath}/Header/JsonDataSubSystem.cpp";
            string insertcppText = "#include \"JsonDataSubsystem.h\"\n\n";
            insertcppText += "UJsonDataSubsystem* UJsonDataSubsystem::jsonDataSubSystem = nullptr;\n\n";
            insertcppText += "void UJsonDataSubsystem::Initialize(FSubsystemCollectionBase& Collection)\n";
            insertcppText += "{\n\tSuper::Initialize(Collection);\n";
            insertcppText += "\tjsonDataSubSystem = this;\n}\n";
            insertcppText += "void UJsonDataSubsystem::Deinitialize()\n{\n";
            insertcppText += "\tSuper::Deinitialize();\n";
            insertcppText += "\tjsonDataSubSystem = nullptr;\n}\n";
            insertcppText += "UJsonDataSubsystem* UJsonDataSubsystem::GetInst()\n";
            insertcppText += "{\r\n\tif (IsValid(jsonDataSubSystem))\n";
            insertcppText += "\t{\n\t\t return jsonDataSubSystem;\n\t}\n";
            insertcppText += "\treturn nullptr;\n}\n";

            File.WriteAllText(makedcppFile, insertcppText);
        }
        #endregion
        #region CommonUtils
        public static string ReturnSaveTextType(string typeString)
        {
            //해당 함수는 C++ 즉 언리얼일때만 실행한다.
            string returnTypeString = typeString;
            if (returnTypeString.Contains("string"))
            {
                returnTypeString = returnTypeString.Replace("string", "FString");
            }
            if (returnTypeString.Contains("[]"))
            {
                returnTypeString = returnTypeString.Replace("[]", "");
                returnTypeString = "TArray<" + returnTypeString + ">";
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
                case "int[]":
                    returnType = typeof(int[]);
                    break;
                case "string[]":
                    returnType = typeof(string[]);
                    break;
                case "float[]":
                case "double[]":
                    returnType = typeof(float[]);
                    break;
                case "char[]":
                    returnType = typeof(char[]);
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
        #endregion CommonUtils
    }
}