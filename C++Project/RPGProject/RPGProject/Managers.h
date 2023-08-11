#pragma once
#include "ManagerSingleton.h"
#include "ObjectActionFactory.h"
#include <string>
#pragma region TestRendering
using namespace std;
class TestRenderingManager : public ManagerSingleton <TestRenderingManager>
{
public:
	static void ClearConsole();
	static void PrintRenderingText(string renderText);
	static void PrintRenderingText(char* renderText);
	static void RenderingLobby();
};
#pragma endregion TestRendering


class InGameManager
{
private:
	E_INGAME_TYPE currentGameType;
	E_INGAME_TEAM_TYPE currentTurnTeam;
	map<E_INGAME_TEAM_TYPE, list<GameActor*>> teamLists; 
	ObejctActionFactory actFactory;
public:
	void CreateAction(GameActor& actObject, GameActor& targetObject, E_OBJECT_ACTION_TYPE actionType);
	void InitGame(E_INGAME_TYPE);
	void CreateTeam();
	void InitMode();
};
class GameManager : public ManagerSingleton<GameManager>
{
public:
	InGameManager ingameManager;

	void InitGame();
	void EnterLobby();
	void EnterStoryMode();
	void EnterPvPMode();
	void EnterShop();
};
class TeamManager 
{
public:
	virtual list<GameActor*> CreateTeamMember(E_INGAME_TEAM_TYPE teamType) = 0;
};
class PVPTeamManager : public TeamManager
{
public:
	list<GameActor*> CreateTeamMember(E_INGAME_TEAM_TYPE teamType) override;
};
class DungeonTeamManager : public TeamManager
{
public:
	list<GameActor*> CreateTeamMember(E_INGAME_TEAM_TYPE teamType) override;
};