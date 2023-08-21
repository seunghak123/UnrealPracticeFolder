#include "Managers.h"
#include <time.h>
#include <Windows.h>
#include <iostream>
#include <algorithm>

using namespace TestTool;

int pageIndex = 0;
GameActor normalUnits[8];
void InsertShopData();
list<GameActor*> PVPTeamManager::CreateTeamMember(E_INGAME_TEAM_TYPE teamType)
{
	list<GameActor*> actorLists;
	switch (teamType)
	{
	case ALPAH_TEAM:
	case BETA_TEAM:
		//������ �� �����͸� �����ͼ�, ������ ����, ĳ���� �����͸� ���� ����
		for (int i = 0; i <GlobalVariables::TEAM_NUMBER_COUNT; i++)
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
		for (int i = 0; i < GlobalVariables::TEAM_NUMBER_COUNT; i++)
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
			newMonsterGameActor->spawnTurn = i / GlobalVariables::TEAM_NUMBER_COUNT + 1;
			//newMonsterGameActor->GetActorObjectInfo().UpdateBasicInfos();
			actorLists.push_back(newMonsterGameActor);
		}
		break;
	}
	return actorLists;
}

void GameManager::InitGame()
{
	InsertShopData();
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
	TestRenderingManager::RenderingLobby();
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
	case 4:
		EnterDeckSetting();
		break;
	}
}
void GameManager::EnterStoryMode()
{
	TestRenderingManager::ClearConsole();
	TestRenderingManager::RenderingStoryMode();
	cout << endl << "��ȣ ���� : ";
	int enterMode = 0;
	std::cin.clear();
	cin >> enterMode;

	switch (enterMode) {
	case 1:

		break;
	case 2:
		EnterDeckSetting();
		break;
	case 99:
		EnterLobby();
		break;
	}
}
void GameManager::EnterPvPMode()
{
	TestRenderingManager::ClearConsole();
}
void GameManager::EnterShop()
{
	TestRenderingManager::ClearConsole();
	TestRenderingManager::RenderingShop();

	cout << endl << "��ȣ ���� : ";
	int enterMode = 0;

	std::cin.clear();
	cin >> enterMode;
	switch (enterMode) {
	case 1:
		pageIndex = 0;
		EnterNormalShop();

		//�⺻ ���� ���� ������
		break;
	case 2:
		pageIndex = 0;
		EnterSellShop();
		//���� ���� ���� ������
		break;
	case 3:

		break;
	case 99:
		EnterLobby();
	}
}
void GameManager::EnterNormalShop()
{

	int linePrintCount = 3;
	int arrayLength = 8;
	int maxIndex = arrayLength % linePrintCount == 0 ? arrayLength / linePrintCount : arrayLength / linePrintCount + 1;
	TestRenderingManager::RenderingUnitLists(normalUnits, arrayLength,linePrintCount,pageIndex);
	TestRenderingManager::RenderingBuySellUnit(normalUnits, arrayLength, linePrintCount, pageIndex, false);
	std::cin.clear();

	char selectNum = 0;
	cin >> selectNum;
	switch (selectNum)
	{
	case '1':
	case '2':
	case '3':
		if (pageIndex * linePrintCount + ( selectNum - '1') < arrayLength)
		{
			UserDataManager::getInstance().userData.BuyCard(GameActor(normalUnits[pageIndex * linePrintCount + (selectNum - '1')]));
		}
		EnterShop();
		break;
	case 'a':
		if (maxIndex >= 2)
		{
			if (pageIndex > 0)
			{
				pageIndex--;
			}
		}
		EnterNormalShop();
		break;
	case 'b':
		if (maxIndex >= 2)
		{
			if (pageIndex < maxIndex - 1)
			{
				pageIndex++;
			}
		}
		EnterNormalShop();
		break;
	case 'e':
		EnterShop();
		break;
	}
	
}
void GameManager::EnterRandomShop()
{
}
void GameManager::EnterSellShop()
{
	tuple<vector<GameActor>, int> cardLists =  UserDataManager::getInstance().userData.GetUserCardLists();

	int linePrintCount = 3;
	vector<GameActor> getArray = get<0>(cardLists); 

	int arrayLength = get<1>(cardLists);
	int maxIndex = arrayLength % linePrintCount == 0 ? arrayLength / linePrintCount : arrayLength / linePrintCount + 1;
	TestRenderingManager::RenderingUnitLists(getArray.data(), arrayLength, linePrintCount, pageIndex);
	TestRenderingManager::RenderingBuySellUnit(getArray.data(), arrayLength, linePrintCount, pageIndex, true);

	std::cin.clear();

	char selectNum = 0;
	cin >> selectNum;
	switch (selectNum)
	{
	case '1':
	case '2':
	case '3':
		if (pageIndex * linePrintCount + (selectNum - '1') < arrayLength)
		{
			UserDataManager::getInstance().userData.SellCard(std::move(new GameActor( getArray.data()[pageIndex * linePrintCount + (selectNum - '1')])));
		}
		EnterShop();
		break;
	case 'a':
		if (maxIndex >= 2)
		{
			if (pageIndex > 0)
			{
				pageIndex--;
			}
		}
		EnterSellShop();
		break;
	case 'b':
		if (maxIndex >= 2)
		{
			if (pageIndex < maxIndex - 1)
			{
				pageIndex++;
			}
		}
		EnterSellShop();
		break;
	case 'e':
		EnterShop();
		break;
	}
}
void GameManager::EnterDeckSetting()
{
	tuple<vector<GameActor>, int> cardLists = UserDataManager::getInstance().userData.GetUserCardLists();

	int linePrintCount = 3;
	vector<GameActor> getArray = get<0>(cardLists);

	int arrayLength = get<1>(cardLists);
	int maxIndex = arrayLength % linePrintCount == 0 ? arrayLength / linePrintCount : arrayLength / linePrintCount + 1;
	TestRenderingManager::RenderingUnitLists(getArray.data(), arrayLength, linePrintCount, pageIndex);
}
void InsertShopData() 
{
	//������ �Է� ����(���� ���� �аų� csv���ϵ� ������ ���� �д� ������ ��ȯ �Ǵ� ���� �����͸� �� ����� �ʿ�)

	normalUnits[0] = GameActor();
	normalUnits[0].GetActorObjectInfo().UpdateBasicInfos(GetDefaultValue(6, 12, 5, 1, 0, 10, 10));
	normalUnits[0].GetActorObjectInfo().SetObjectName("�ü�");
	normalUnits[0].GetActorObjectInfo().SetPriceValue(50, 25);

	normalUnits[1] = GameActor();
	normalUnits[1].GetActorObjectInfo().UpdateBasicInfos(GetDefaultValue(6, 20, 3, 3, 0, 10, 15));
	normalUnits[1].GetActorObjectInfo().SetObjectName("����");
	normalUnits[1].GetActorObjectInfo().SetPriceValue(70, 35);

	normalUnits[2] = GameActor();
	normalUnits[2].GetActorObjectInfo().UpdateBasicInfos(GetDefaultValue(6, 8, 20, 0, 0, 10, 20));
	normalUnits[2].GetActorObjectInfo().SetObjectName("������");
	normalUnits[2].GetActorObjectInfo().SetPriceValue(100, 50);

	normalUnits[3] = GameActor();
	normalUnits[3].GetActorObjectInfo().UpdateBasicInfos(GetDefaultValue(6, 12, 5, 1, 0, 10, 10));
	normalUnits[3].GetActorObjectInfo().SetObjectName("�ü�2");
	normalUnits[3].GetActorObjectInfo().SetPriceValue(50, 25);

	normalUnits[4] = GameActor();
	normalUnits[4].GetActorObjectInfo().UpdateBasicInfos(GetDefaultValue(6, 20, 3, 3, 0, 10, 15));
	normalUnits[4].GetActorObjectInfo().SetObjectName("����2");
	normalUnits[4].GetActorObjectInfo().SetPriceValue(70, 35);

	normalUnits[5] = GameActor();
	normalUnits[5].GetActorObjectInfo().UpdateBasicInfos(GetDefaultValue(6, 8, 20, 0, 0, 10, 20));
	normalUnits[5].GetActorObjectInfo().SetObjectName("������2");
	normalUnits[5].GetActorObjectInfo().SetPriceValue(100, 50);

	normalUnits[6] = GameActor();
	normalUnits[6].GetActorObjectInfo().UpdateBasicInfos(GetDefaultValue(6, 12, 5, 1, 0, 10, 10));
	normalUnits[6].GetActorObjectInfo().SetObjectName("�ü�3");
	normalUnits[6].GetActorObjectInfo().SetPriceValue(50, 25);

	normalUnits[7] = GameActor();
	normalUnits[7].GetActorObjectInfo().UpdateBasicInfos(GetDefaultValue(6, 20, 3, 3, 0, 10, 15));
	normalUnits[7].GetActorObjectInfo().SetObjectName("����3");
	normalUnits[7].GetActorObjectInfo().SetPriceValue(70, 35);

}