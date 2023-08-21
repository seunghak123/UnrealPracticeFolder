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
		TestRenderingManager::PrintRenderingText("모험을 시작합니다.");
		TestRenderingManager::PrintRenderingText("");
		TestRenderingManager::PrintRenderingText("===모드를 선택해주세요===");
		TestRenderingManager::PrintRenderingText("1.스토리모드");
		TestRenderingManager::PrintRenderingText("2.PvP모드");
		TestRenderingManager::PrintRenderingText("3.상점");
		TestRenderingManager::PrintRenderingText("4.덱 세팅");
	}
	void TestRenderingManager::RenderingShop()
	{
		TestRenderingManager::PrintRenderingText("1.유닛 구매");
		TestRenderingManager::PrintRenderingText("2.유닛 판매");
		TestRenderingManager::PrintRenderingText("3.랜덤 유닛 구매");
		TestRenderingManager::PrintRenderingText("99.로비로 이동");
	}

	void TestRenderingManager::RenderingUnitLists(GameActor* renderingActors, int arrayLength,int linePrintCount,int pageIndex )
	{
		ClearConsole();
		cout << "일반 유닛 상점" << endl;
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
			string printString = "가격 :";
			printString += to_string(renderingActors[pageIndex * linePrintCount + j].GetActorObjectInfo().GetBuyPriceValue());
			cout << left << setw(20) << printString;
		}
		cout << endl;
		
		if (maxIndex >= 2)
		{
			cout << "구매 1,2,3 키 나가기(e)" << endl;
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
		cout << "입력 : ";
	}
}
