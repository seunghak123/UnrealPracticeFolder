#pragma once
#include "SystemInfo.h"
#include <map>
#include <list>
#include <functional>
#include <memory>
#include <cstdarg>
#include <string>
using namespace std;

class GameActor;

struct Vector2
{
	float x, y;
};
struct DamageStruct
{
	public :
		GameActor* ownActor;
		GameActor* targetActor;
		map<E_STATVALUE_TYPE, float> attackInfo;
};

class ObjectAction 
{
public:	
	E_OBJECT_ACTION_TYPE objectActionType;
	virtual void Action() =0;
	function<void()> fucLambdaPointer;
};
class AttackAction : public ObjectAction {
public:
	AttackAction(GameActor*, GameActor*);
	void Action() override;
	void RegistTargetData(GameActor* ownObject, GameActor* targetObject);
	void ActionWork();
	void ApplyDamage();
private:
	DamageStruct currentDamageStruct;
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
	void ActionWork();
private:
	DamageStruct currentDamageStruct;
};


class ObjectInfo {
public :
	void UpdateBasicInfos(map<E_OBJECTINFO, int>);
	void UpdateInfo(E_OBJECTINFO, int);
	bool HasInfoValue(E_OBJECTINFO);
	int GetInfoValue(E_OBJECTINFO);
	void SetObjectName(string);
	string GetObjectName();
private :
	string objectName;
	int buyValue;
	int sellValue;
	E_RARITY objectRarity;	
	map<E_OBJECTINFO, int> objectInfo;
};

class GameActor
{
public:
	void RegistNextAction(ObjectAction* nextAction);
	void ActActions();
	ObjectInfo& GetActorObjectInfo();

	~GameActor() {
		
	}
private:
	ObjectInfo objectInfo;
	
	list<std::unique_ptr<ObjectAction> > playActionLists;
};
class DungeonMonsterGameActor : public GameActor
{
public:
	int spawnTurn;
private :
};
/// <summary>
/// 기본 스탯 세팅
/// </summary>
/// <param name="length"></param>
/// <param name="체력, 공격력, 방어력, 실드, 스피드 , 스피드 소모량"></param>
/// <returns></returns>
map<E_OBJECTINFO, int> GetDefaultValue(int length,...) 
{
	map<E_OBJECTINFO, int> returnValueData;
	va_list argulists;
	va_start(argulists, length);
	for (int i = 0; i < E_OBJECTINFO::END; i++) {
		
		if (i >= length) {
			returnValueData.insert(i, 1);
			continue;
		}

		int infoValue = va_arg(argulists, int);
		returnValueData.insert(i, infoValue);
	}
	va_end(argulists);

	return returnValueData;
};