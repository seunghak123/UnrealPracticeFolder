#include "Managers.h"

void GameManager::CreateAction(GameActor& actObject, GameActor& targetObject, E_OBJECT_ACTION_TYPE actionType)
{
	actFactory.InsertObjectAction(actObject, targetObject, actionType);
}

void GameManager::CreateTeam()
{
	//ENum값에 따라서 팀 생성 , 모드에 따라서 3팀이 넘을수도 안넘을 수도 있다.
}
