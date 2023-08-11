#include "Managers.h"

void InGameManager::CreateAction(GameActor& actObject, GameActor& targetObject, E_OBJECT_ACTION_TYPE actionType)
{
	actFactory.InsertObjectAction(actObject, targetObject, actionType);
}

void InGameManager::InitGame(E_INGAME_TYPE ingameType)
{

	this->CreateTeam();
}

void InGameManager::CreateTeam()
{
	switch (this->currentGameType)
	{
	case E_INGAME_TYPE::PVP_MODE:
	{
		PVPTeamManager teamManager;
		teamLists[E_INGAME_TEAM_TYPE::ALPAH_TEAM] = teamManager.CreateTeamMember(E_INGAME_TEAM_TYPE::ALPAH_TEAM);
		teamLists[E_INGAME_TEAM_TYPE::BETA_TEAM] = teamManager.CreateTeamMember(E_INGAME_TEAM_TYPE::BETA_TEAM);
	}
	break;
	case E_INGAME_TYPE::DUNGEON_MODE:
	{
		DungeonTeamManager teamManager;
		teamLists[E_INGAME_TEAM_TYPE::USER_TEAM] = teamManager.CreateTeamMember(E_INGAME_TEAM_TYPE::USER_TEAM);
		teamLists[E_INGAME_TEAM_TYPE::MONSTER_TEAM] = teamManager.CreateTeamMember(E_INGAME_TEAM_TYPE::MONSTER_TEAM);
	}
	break;
	}
}

void InGameManager::InitMode()
{
}

