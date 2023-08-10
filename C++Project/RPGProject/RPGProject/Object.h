#pragma once
#include "SystemInfo.h"
#include <map>
#include <list>
using namespace std;

class GameActor;

struct Vector2
{
	float x, y;
};
struct DamageStruct
{
	public :
		GameActor* targetActor;
		map<E_DAMAGE_TYPE, float> attackInfo;
};

class ObjectAction 
{
public:	
	E_OBJECT_ACTION_TYPE objectActionType;
	virtual void Action();
};
class AttackAction : public ObjectAction {
public:
	void Action() override;
	void ActionWork(DamageStruct damageStruct);
};
class MoveAction : public ObjectAction {
private:
	Vector2 objectMoveVector;
public:
	void Action() override;
	void ActionWork(Vector2 moveVector);
};
class HealAction : public ObjectAction {
public :
	void Action() override;
	void ActionWork(GameActor* target, DamageStruct damageStruct);
};


class ObjectInfo {
public:
	void UpdateBasicInfos(map<E_OBJECTINFO, int>);
	void UpdateInfo(E_OBJECTINFO, int);
	bool HasInfoValue(E_OBJECTINFO);
	int GetInfoValue(E_OBJECTINFO);
#if Test_Code
	void PrintValues();
#endif // Test_Code

private :
	E_RARITY objectRarity;	
	map<E_OBJECTINFO, int> objectInfo;
};

class GameActor
{
public:
	void RegistNextAction(ObjectAction* nextAction);
	void ActActions();
	ObjectInfo& GetActorObjectInfo();
private:
	ObjectInfo objectInfo;
	list<ObjectAction*> playActionLists;
};