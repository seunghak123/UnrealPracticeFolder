#pragma once
#include <fstream>
#include <string>

class FileUtils {
public:
	template <typename T>
	static T FileRead(std::string fileName) {
		std::ifstream inputFile(fileName); // ���� ����

		if (!inputFile.is_open()) {
			std::cerr << "Failed to open the file." << std::endl;
			return nullptr;
		}
		std::string line;
		while (std::getline(inputFile, line)) {
			std::cout << line << std::endl; // �� �پ� �о� ���
		}
		//Json���̺귯���� �̿��Ͽ� line�� ���� Ŭ���� �����͸� fileData�� �־��ش�
		T fileData = default;
		return fileData;
	}
	template <typename T>
	static void FileSave(std::string fileName, T SaveData)
	{
		//Ư�� ���� ��η� fileName���Ͽ� SaveData�� ��ȯ�ؼ� �����Ѵ�
		//byte[] bytedatas = SaveData.
	}
};