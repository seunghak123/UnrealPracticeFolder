#pragma once
#include "SystemInfo.h"
#include <map>
#include <list>
#include <functional>
#include <memory>
#include <cstdarg>
#include <string>
#include <cmath>
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
	ObjectInfo(const ObjectInfo& other) :
		objectUID(other.objectUID),
		objectName(other.objectName),
		objectRarity(other.objectRarity),
		buyValue(other.buyValue),
		sellValue(other.sellValue)
	{
		this->objectInfo = map<E_OBJECTINFO, int>();
		for (auto datas : other.objectInfo) 
		{
			this->objectInfo[datas.first] = datas.second;
		}
	}
	~ObjectInfo()
	{
		objectInfo.clear();
	}

	void UpdateBasicInfos(map<E_OBJECTINFO, int>);
	void UpdateInfo(E_OBJECTINFO, int);
	bool HasInfoValue(E_OBJECTINFO) ;
	int GetInfoValue(E_OBJECTINFO) ;
	void SetObjectName(string);
	string GetObjectName();
	map<E_OBJECTINFO, int> GetObjectInfoMap();
	/// <summary>
	/// 카드 가격 정하는 함수(초기화 할때만 호출 차후 엑셀 데이터에서 변경할 것
	/// </summary>
	/// <param name="buyPrice">구매 가격</param>
	/// <param name="sellPrice">판매 가격</param>
	void SetPriceValue(int buyPrice, int sellPrice);
	int GetBuyPriceValue();
	int GetSellPriceValue();
	string GetUniqueId() {
		return objectUID;
	}
	ObjectInfo() {
		objectUID = GenerateUUID();
	}
private :
	string objectUID;
	string objectName;
	int buyValue;
	int sellValue;
	E_RARITY objectRarity;	
	map<E_OBJECTINFO, int> objectInfo;
};

class GameActor
{
public:
	void RegistNextAction(ObjectAction* nextAction) 
	{
		this->playActionLists.push_back(shared_ptr<ObjectAction>(nextAction));
	};
	void ActActions();
	ObjectInfo& GetActorObjectInfo();
	GameActor() 
	{
		
	}
	GameActor(const GameActor& other) 
	{
		objectInfo = ObjectInfo(other.objectInfo);
	}
	GameActor(const ObjectInfo& infoData) {
		objectInfo = ObjectInfo(infoData);
	}
	~GameActor() 
	{
		playActionLists.clear();
	}
private:
	ObjectInfo objectInfo;
	
	list<shared_ptr<ObjectAction>> playActionLists;
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
extern map<E_OBJECTINFO, int> GetDefaultValue(int length, ...);
extern const std::map<E_OBJECTINFO, string> INFOTYPE_TOSTRING;
extern ObjectInfo GetRandomObjectInfo(int positionNumber,int unitLevel =0) 
{
	srand(clock() + positionNumber);
	int randomUnitType = rand() % E_RANDOM_UNIT_TYPE::END_UNIT_TYPE;
	//100%기준으로
	int percentValue[E_RANDOM_UNIT_TYPE::END_UNIT_TYPE][6] = { {2,4,1,0,3,2},{5,2,3,0,2,3}, {3,10,1,4,2,4} };
	ObjectInfo newInfoObjext = ObjectInfo();

	switch (randomUnitType) {
	case E_RANDOM_UNIT_TYPE::WARRIOR:
		newInfoObjext.SetObjectName("전사");
		break;
	case E_RANDOM_UNIT_TYPE::ARCHER:
		newInfoObjext.SetObjectName("궁수");
		break;
	case E_RANDOM_UNIT_TYPE::MAGICAN:
		newInfoObjext.SetObjectName("마법사");
		break;
	}
	float upgradeValue = pow(1.1, unitLevel);
	
	int hpValue = floor( percentValue[randomUnitType][0]* upgradeValue);
	int attackValue = floor(percentValue[randomUnitType][1] * upgradeValue);
	int defenceValue = floor(percentValue[randomUnitType][2] * upgradeValue);
	int sheildValue = floor(percentValue[randomUnitType][3] * upgradeValue);
	int speedValue = floor(percentValue[randomUnitType][4] * upgradeValue);
	int consumeValue = floor(percentValue[randomUnitType][5] / upgradeValue);

	newInfoObjext.UpdateBasicInfos(GetDefaultValue(6, hpValue, attackValue, defenceValue, sheildValue, speedValue, consumeValue));
	return newInfoObjext;
}
