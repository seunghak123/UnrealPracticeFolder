#include "Managers.h"

void GameManager::CreateAction(GameActor actObject, GameActor targetObject, E_OBJECT_ACTION_TYPE actionType)
{
	actFactory.InsertObjectAction(actObject, targetObject, actionType);
}
