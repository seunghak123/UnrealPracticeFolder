#pragma once
#include "ManagerSingleton.h"
#include "ObjectActionFactory.h"
class GameManager : public ManagerSingleton < GameManager> 
{
private:
	ObejctActionFactory actFactory;
public:
	void CreateAction(GameActor actObject, GameActor targetObject, E_OBJECT_ACTION_TYPE actionType);
};