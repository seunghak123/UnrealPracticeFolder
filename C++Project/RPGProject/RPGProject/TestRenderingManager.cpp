#include "Managers.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string>
#include <conio.h>

using namespace std;
namespace TestTool 
{
	void TestRenderingManager::ClearConsole()
	{
		system("cls");
	}
	void TestRenderingManager::PrintRenderingText(char* renderText)
	{
		cout << renderText << endl;
	}
	void TestRenderingManager::PrintRenderingText(string renderText)
	{
		cout << renderText << endl;
	}
	void TestRenderingManager::RenderingLobby()
	{
		TestRenderingManager::PrintRenderingText("������ �����մϴ�.");
		TestRenderingManager::PrintRenderingText("");
		TestRenderingManager::PrintRenderingText("===��带 �������ּ���===");
		TestRenderingManager::PrintRenderingText("1.���丮���");
		TestRenderingManager::PrintRenderingText("2.PvP���");
		TestRenderingManager::PrintRenderingText("3.����");
		TestRenderingManager::PrintRenderingText("4.�� ����");
	}
	void TestRenderingManager::RenderingShop()
	{
		TestRenderingManager::PrintRenderingText("1.���� ����");
		TestRenderingManager::PrintRenderingText("2.���� �Ǹ�");
		TestRenderingManager::PrintRenderingText("3.���� ���� ����");
		TestRenderingManager::PrintRenderingText("99.�κ�� �̵�");
	}

	void TestRenderingManager::RenderingUnitLists(GameActor* renderingActors, int arrayLength,int linePrintCount,int pageIndex )
	{
		ClearConsole();
		cout << "�Ϲ� ���� ����" << endl;
		cout << right << setw(40) << UserDataManager::getInstance().userData.GetUserWealth(E_WEALTH_TYPE::GOLD)<<endl;
		int maxIndex = arrayLength%linePrintCount == 0? arrayLength / linePrintCount : arrayLength / linePrintCount + 1;

		for (int j = 0; j < linePrintCount && pageIndex * linePrintCount + j < arrayLength; j++)
		{
			cout << left << setw(20) << renderingActors[pageIndex*linePrintCount + j].GetActorObjectInfo().GetObjectName();
		}
		cout << endl;
		for (auto autoInfo : INFOTYPE_TOSTRING)
		{
			for (int j = 0; j < linePrintCount && pageIndex * linePrintCount + j < arrayLength; j++)
			{
				string printString = INFOTYPE_TOSTRING.at(autoInfo.first);
				printString += to_string(renderingActors[pageIndex * linePrintCount + j].GetActorObjectInfo().GetInfoValue(autoInfo.first));
				cout << left << setw(20) << printString;
			}
			cout << endl;
		}
		cout << endl;
		for (int j = 0; j < linePrintCount && pageIndex * linePrintCount + j < arrayLength; j++)
		{
			string printString = "���� :";
			printString += to_string(renderingActors[pageIndex * linePrintCount + j].GetActorObjectInfo().GetBuyPriceValue());
			cout << left << setw(20) << printString;
		}
		cout << endl;
		
		if (maxIndex >= 2)
		{
			cout << "���� 1,2,3 Ű ������(e)" << endl;
			string pagingString;
			if (pageIndex > 0)
			{
				pagingString += "<-(a key)";
			}
			if (pageIndex < maxIndex-1)
			{
				pagingString += "(b key) ->";
			}
			cout << left << setw(20) << pagingString<<endl;
		}
		cout << "�Է� : ";
	}
}
