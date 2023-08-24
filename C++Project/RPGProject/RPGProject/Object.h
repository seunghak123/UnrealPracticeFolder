#pragma once
#include "SystemInfo.h"
#include <map>
#include <list>
#include <functional>
#include <memory>
#include <cstdarg>
#include <string>
#include <cmath>
#include <ctime>
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
	/// ī�� ���� ���ϴ� �Լ�(�ʱ�ȭ �Ҷ��� ȣ�� ���� ���� �����Ϳ��� ������ ��
	/// </summary>
	/// <param name="buyPrice">���� ����</param>
	/// <param name="sellPrice">�Ǹ� ����</param>
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
/// �⺻ ���� ����
/// </summary>
/// <param name="length"></param>
/// <param name="ü��, ���ݷ�, ����, �ǵ�, ���ǵ� , ���ǵ� �Ҹ�"></param>
/// <returns></returns>
extern map<E_OBJECTINFO, int> GetDefaultValue(int length, ...);
extern const std::map<E_OBJECTINFO, string> INFOTYPE_TOSTRING;
extern ObjectInfo GetRandomObjectInfo(int positionNumber, int unitLevel = 0);
