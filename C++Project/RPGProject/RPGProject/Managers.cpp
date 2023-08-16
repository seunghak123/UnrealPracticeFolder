#include "Managers.h"
#include <time.h>
#include <Windows.h>
#include <iostream>
#include <algorithm>
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
	TestRenderingManager::RenderingLobby();
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
	TestRenderingManager::RenderingShop();

	cout << endl << "번호 선택 : ";
	int enterMode = 0;

	std::cin.clear();
	cin >> enterMode;
	switch (enterMode) {
	case 1:
		TestRenderingManager::RenderingBuyingNormalUnit();
		//기본 상점 유닛 렌더링
		break;
	case 2:
		//현재 유저 유닛 렌더링
		break;
	case 3:
		//일반유닛인데 약간 스텟이 랜덤인 유닛 제공 다만 종류는 랜덤
		break;
	}
}
