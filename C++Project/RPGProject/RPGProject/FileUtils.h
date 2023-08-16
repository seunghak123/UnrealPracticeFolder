#pragma once
#include <fstream>
#include <string>

class FileUtils {
public:
	template <typename T>
	static T FileRead(std::string fileName) {
		std::ifstream inputFile(fileName); // 파일 열기

		if (!inputFile.is_open()) {
			std::cerr << "Failed to open the file." << std::endl;
			return nullptr;
		}
		std::string line;
		while (std::getline(inputFile, line)) {
			std::cout << line << std::endl; // 한 줄씩 읽어 출력
		}
		//Json라이브러리를 이용하여 line을 읽은 클래스 데이터를 fileData에 넣어준다
		T fileData = default;
		return fileData;
	}
	template <typename T>
	static void FileSave(std::string fileName, T SaveData)
	{
		//특정 파일 경로로 fileName파일에 SaveData를 변환해서 저장한다
		//byte[] bytedatas = SaveData.
	}
};