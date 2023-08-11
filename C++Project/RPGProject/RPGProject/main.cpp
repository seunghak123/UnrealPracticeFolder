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
	//여기서는  Info Value들을 Json등이나 저장된 Manager에서 데이터를 긁어서 사용
	ateamActor.GetActorObjectInfo().UpdateBasicInfos(ateamBasicInfoValues);
	GameManager& instance = GameManager::getInstance();

	ateamActor.RegistNextAction(new AttackAction());


	ateamActor.ActActions();
}