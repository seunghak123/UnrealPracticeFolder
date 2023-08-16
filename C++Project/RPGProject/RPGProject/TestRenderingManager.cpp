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
}

void TestRenderingManager::RenderingBuyingNormalUnit()
{
	GameActor normalUnits[3];
	//������ �Է� ����(���� ���� �аų� csv���ϵ� ������ ���� �д� ������ ��ȯ �Ǵ� ���� �����͸� �� ����� �ʿ�)

	normalUnits[0] = GameActor();
	normalUnits[0].GetActorObjectInfo().UpdateBasicInfos(GetDefaultValue(6, 12, 5 , 1, 0, 10, 10));
	normalUnits[0].GetActorObjectInfo().SetObjectName("�ü�");

	normalUnits[1] = GameActor();
	normalUnits[1].GetActorObjectInfo().UpdateBasicInfos(GetDefaultValue(6, 20, 3, 3, 0, 10, 15));
	normalUnits[1].GetActorObjectInfo().SetObjectName("����");

	normalUnits[2] = GameActor();
	normalUnits[2].GetActorObjectInfo().UpdateBasicInfos(GetDefaultValue(6, 8, 20, 0, 0, 10, 20));
	normalUnits[2].GetActorObjectInfo().SetObjectName("������");

	//������ �Է� ����
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
