#include "Managers.h"
#include <iostream>
#include <algorithm>

using namespace std;
void TestRenderingManager::ClearConsole()
{
	system("cls");
}
void TestRenderingManager::PrintRenderingText(string renderText)
{
	cout << renderText << endl;
}

void TestRenderingManager::PrintRenderingText(char* renderText)
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
}

void TestRenderingManager::RenderingBuyingNormalUnit()
{
	GameActor normalUnits[3];
	//데이터 입력 구문(차후 파일 읽거나 csv파일등 데이터 파일 읽는 것으로 변환 또는 유닛 데이터를 알 방법이 필요)

	normalUnits[0] = GameActor();
	normalUnits[0].GetActorObjectInfo().UpdateBasicInfos(GetDefaultValue(6, 12, 5 , 1, 0, 10, 10));
	normalUnits[0].GetActorObjectInfo().SetObjectName("궁수");

	normalUnits[1] = GameActor();
	normalUnits[1].GetActorObjectInfo().UpdateBasicInfos(GetDefaultValue(6, 20, 3, 3, 0, 10, 15));
	normalUnits[1].GetActorObjectInfo().SetObjectName("전사");

	normalUnits[2] = GameActor();
	normalUnits[2].GetActorObjectInfo().UpdateBasicInfos(GetDefaultValue(6, 8, 20, 0, 0, 10, 20));
	normalUnits[2].GetActorObjectInfo().SetObjectName("마법사");

	//데이터 입력 구문
	list<GameActor> normalUnitLists;
	std::copy_if(std::begin(normalUnits), std::end(normalUnits), std::back_inserter(normalUnitLists), [](GameActor insertActor)
		{
			return 1;
		}
	);
	RenderingUnitLists(normalUnits, 3);
}
void TestRenderingManager::RenderingUnitLists(GameActor* renderingActors,int arrayLength)
{
	
}
