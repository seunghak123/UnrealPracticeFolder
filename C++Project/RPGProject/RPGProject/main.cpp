#include <iostream>
#include <algorithm>
#include <vector>
#include "Object.h"
#include "Managers.h"
#include "ManagerSingleton.h"
#include "SystemInfo.h"
using namespace std;

void main() {
	GameManager::getInstance().InitGame();
	//GameActor ateamActor;
	//GameActor bteamActor;

	//map<E_OBJECTINFO, int> ateamBasicInfoValues;
	////���⼭��  Info Value���� Json���̳� ����� Manager���� �����͸� �ܾ ���
	//ateamActor.GetActorObjectInfo().UpdateBasicInfos(ateamBasicInfoValues);
	//InGameManager& instance = GameManager::getInstance().ingameManager;
	////�ΰ��� �Ŵ���
	//instance.CreateAction(ateamActor, bteamActor, E_OBJECT_ACTION_TYPE::ATTACK_OTHER);
	//
	//ateamActor.ActActions();
	//bteamActor.ActActions();
}