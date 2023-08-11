#include "Managers.h"
#include <time.h>
#include <Windows.h>
#include <iostream>
list<GameActor*> PVPTeamManager::CreateTeamMember(E_INGAME_TEAM_TYPE teamType)
{
	list<GameActor*> actorLists;
	switch (teamType)
	{
	case ALPAH_TEAM:
	case BETA_TEAM:
		//유저의 팀 데이터를 가져와서, 데이터 복사, 캐릭터 데이터를 팀에 세팅
		for (int i = 0; i < TEAM_NUMBER_COUNT; i++)
		{
			GameActor* newGameActor = new GameActor();
			//기본데이터 입력
			//newGameActor->GetActorObjectInfo().UpdateBasicInfos();
			actorLists.push_back(newGameActor);
		}
		break;
		//다른 팀의 경우는 생성불가
	}
	return actorLists;
}

list<GameActor*> DungeonTeamManager::CreateTeamMember(E_INGAME_TEAM_TYPE teamType)
{
	list<GameActor*> actorLists;
	switch (teamType)
	{
	case USER_TEAM:
		//유저의 팀 데이터를 가져와서, 데이터 복사, 캐릭터 데이터를 팀에 세팅
		for (int i = 0; i < TEAM_NUMBER_COUNT; i++)
		{
			GameActor* newGameActor = new GameActor();
			//기본데이터 입력
			//newGameActor->GetActorObjectInfo().UpdateBasicInfos();
			actorLists.push_back(newGameActor);
		}
		break;
	case MONSTER_TEAM:
		int teamNumberCount = 12;
		for (int i = 0; i < teamNumberCount; i++) 
		{
			DungeonMonsterGameActor* newMonsterGameActor = new DungeonMonsterGameActor();
			newMonsterGameActor->spawnTurn = i / TEAM_NUMBER_COUNT + 1;
			//newMonsterGameActor->GetActorObjectInfo().UpdateBasicInfos();
			actorLists.push_back(newMonsterGameActor);
		}
		break;
	}
	return actorLists;
}

void GameManager::InitGame()
{
	system("mode con cols=160 lines=40 | title TextRPG");
	TestRenderingManager::PrintRenderingText("게임을 시작합니다");
	Sleep(1000);
	TestRenderingManager::ClearConsole();
	TestRenderingManager::PrintRenderingText("게임을 시작합니다.");
	Sleep(1000);
	TestRenderingManager::ClearConsole();
	TestRenderingManager::PrintRenderingText("게임을 시작합니다..");
	Sleep(1000);
	TestRenderingManager::ClearConsole();

	//기본 유저데이터 입력(기본적인 유닛)

	EnterLobby();
}

void GameManager::EnterLobby()
{
	TestRenderingManager::ClearConsole();
	TestRenderingManager::PrintRenderingText("모험을 시작합니다.");
	TestRenderingManager::PrintRenderingText("");
	TestRenderingManager::PrintRenderingText("===모드를 선택해주세요===");
	TestRenderingManager::PrintRenderingText("1.스토리모드");
	TestRenderingManager::PrintRenderingText("2.PvP모드");
	TestRenderingManager::PrintRenderingText("3.상점");
	TestRenderingManager::PrintRenderingText("4.덱 세팅");
	Sleep(1000);
	cout <<endl<< "번호 선택 : ";
	int enterMode = 0;
	std::cin.clear();
	cin >> enterMode;

	switch (enterMode) {
	case 1:
		EnterStoryMode();
		break;
	case 2:
		EnterPvPMode();
		break;
	case 3:
		EnterShop();
		break;
	}
}

void GameManager::EnterStoryMode()
{
	TestRenderingManager::ClearConsole();
}

void GameManager::EnterPvPMode()
{
	TestRenderingManager::ClearConsole();
}

void GameManager::EnterShop()
{
	TestRenderingManager::ClearConsole();
	TestRenderingManager::PrintRenderingText("1.유닛 구매");
	TestRenderingManager::PrintRenderingText("2.유닛 판매");
	TestRenderingManager::PrintRenderingText("3.랜덤 유닛 구매");
}
