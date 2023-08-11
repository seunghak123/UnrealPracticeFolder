#include <iostream>
#include <algorithm>
#include <vector>
#include "Object.h"
#include "Managers.h"
#include "ManagerSingleton.h"
using namespace std;

void main() {
	GameActor ateamActor;
	GameActor bteamActor;

	map<E_OBJECTINFO, int> ateamBasicInfoValues;
	//���⼭��  Info Value���� Json���̳� ����� Manager���� �����͸� �ܾ ���
	ateamActor.GetActorObjectInfo().UpdateBasicInfos(ateamBasicInfoValues);
	GameManager& instance = GameManager::getInstance();

	ateamActor.RegistNextAction(new AttackAction());


	ateamActor.ActActions();
}