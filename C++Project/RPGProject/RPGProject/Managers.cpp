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
		//������ �� �����͸� �����ͼ�, ������ ����, ĳ���� �����͸� ���� ����
		for (int i = 0; i < TEAM_NUMBER_COUNT; i++)
		{
			GameActor* newGameActor = new GameActor();
			//�⺻������ �Է�
			//newGameActor->GetActorObjectInfo().UpdateBasicInfos();
			actorLists.push_back(newGameActor);
		}
		break;
		//�ٸ� ���� ���� �����Ұ�
	}
	return actorLists;
}

list<GameActor*> DungeonTeamManager::CreateTeamMember(E_INGAME_TEAM_TYPE teamType)
{
	list<GameActor*> actorLists;
	switch (teamType)
	{
	case USER_TEAM:
		//������ �� �����͸� �����ͼ�, ������ ����, ĳ���� �����͸� ���� ����
		for (int i = 0; i < TEAM_NUMBER_COUNT; i++)
		{
			GameActor* newGameActor = new GameActor();
			//�⺻������ �Է�
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
	TestRenderingManager::PrintRenderingText("������ �����մϴ�");
	Sleep(1000);
	TestRenderingManager::ClearConsole();
	TestRenderingManager::PrintRenderingText("������ �����մϴ�.");
	Sleep(1000);
	TestRenderingManager::ClearConsole();
	TestRenderingManager::PrintRenderingText("������ �����մϴ�..");
	Sleep(1000);
	TestRenderingManager::ClearConsole();

	//�⺻ ���������� �Է�(�⺻���� ����)

	EnterLobby();
}

void GameManager::EnterLobby()
{
	TestRenderingManager::ClearConsole();
	TestRenderingManager::PrintRenderingText("������ �����մϴ�.");
	TestRenderingManager::PrintRenderingText("");
	TestRenderingManager::PrintRenderingText("===��带 �������ּ���===");
	TestRenderingManager::PrintRenderingText("1.���丮���");
	TestRenderingManager::PrintRenderingText("2.PvP���");
	TestRenderingManager::PrintRenderingText("3.����");
	TestRenderingManager::PrintRenderingText("4.�� ����");
	Sleep(1000);
	cout <<endl<< "��ȣ ���� : ";
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
	TestRenderingManager::PrintRenderingText("1.���� ����");
	TestRenderingManager::PrintRenderingText("2.���� �Ǹ�");
	TestRenderingManager::PrintRenderingText("3.���� ���� ����");
}
