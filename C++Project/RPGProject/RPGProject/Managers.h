#pragma once
#include "ManagerSingleton.h"
#include "ObjectActionFactory.h"
class GameManager : public ManagerSingleton < GameManager> 
{
private:
	E_INGAME_TEAM_TYPE currentTurnTeam;
	map<E_INGAME_TEAM_TYPE, list<GameActor>> teamLists; 
	ObejctActionFactory actFactory;
public:
	void CreateAction(GameActor& actObject, GameActor& targetObject, E_OBJECT_ACTION_TYPE actionType);
	void CreateTeam();
};