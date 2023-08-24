#include "Object.h"
#include "SystemInfo.h"
#include <iostream>
#include "Managers.h"

using namespace TestTool;
void ObjectInfo::UpdateBasicInfos(map<E_OBJECTINFO, int> insertMap)
{
	for (const auto& pair : insertMap) {
		this->objectInfo[pair.first] = pair.second;
	}
}
void ObjectInfo::UpdateInfo(E_OBJECTINFO infoType, int infoValue)
{
	this->objectInfo[infoType] = infoValue;
}
int ObjectInfo::GetInfoValue(E_OBJECTINFO infoType) 
{
	if (this->HasInfoValue(infoType)) 
	{
		return this->objectInfo[infoType];
	}
	return 0;
}
void ObjectInfo::SetObjectName(string objectName)
{
	this->objectName = objectName;
}
string ObjectInfo::GetObjectName()
{
	return this->objectName;
}
map<E_OBJECTINFO, int> ObjectInfo::GetObjectInfoMap()
{
	return this->objectInfo;
}
void ObjectInfo::SetPriceValue(int buyPrice, int sellPrice)
{
	this->buyValue = buyPrice;
	this->sellValue = sellPrice;
}
int ObjectInfo::GetBuyPriceValue()
{
	return this->buyValue;
}
int ObjectInfo::GetSellPriceValue()
{
	return this->sellValue;
}
bool ObjectInfo::HasInfoValue(E_OBJECTINFO infoType)
{
	auto it = this->objectInfo.find(infoType);
	if (it == this->objectInfo.end()) {
		return false;
	}

	return true;
}
ObjectInfo& GameActor::GetActorObjectInfo()
{
	return this->objectInfo;
}
#pragma region  ActionFuction

#pragma region AttackAtion
AttackAction::AttackAction(GameActor* ownActor, GameActor* targetActor)
{
	RegistTargetData(ownActor, targetActor);
}
void AttackAction::Action()
{
	DamageStruct newStruct;
	newStruct.targetActor = nullptr;
	ActionWork();
}
void AttackAction::RegistTargetData(GameActor* ownObject, GameActor* targetObject)
{
	this->currentDamageStruct.targetActor = targetObject;
}
void AttackAction::ActionWork()
{
	this->fucLambdaPointer = [this]()
	{
		this->ApplyDamage();
	};
	
	//렌더링 과정 

	this->fucLambdaPointer();
}
void AttackAction::ApplyDamage()
{

}
#pragma endregion
#pragma region MoveAction
void MoveAction::Action()
{
}
void MoveAction::ActionWork(Vector2 moveVector)
{
	//캐릭터 위치 변경 
}
#pragma endregion MoveAction
#pragma region HealAction
void HealAction::Action()
{
}
void HealAction::ActionWork()
{

}
#pragma endregion HealAction
#pragma endregion ActionFuction

map<E_OBJECTINFO, int> GetDefaultValue(int length, ...)
{
	map<E_OBJECTINFO, int> returnValueData;
	va_list argulists;
	va_start(argulists, length);
	for (int i = 0; i < E_OBJECTINFO::INFO_END; i++) {

		if (i >= length) {
			returnValueData[(E_OBJECTINFO)i]= 1;
			continue;
		}

		int infoValue = va_arg(argulists, int);
		returnValueData[(E_OBJECTINFO)i] = infoValue;
	}
	va_end(argulists);

	return returnValueData;
};

const std::map<E_OBJECTINFO,string> INFOTYPE_TOSTRING = {
	{E_OBJECTINFO::ATTACK,"공격력 :"},{E_OBJECTINFO::DEFENCE,"방어력 :"},
	{E_OBJECTINFO::HP,"체력 :"},{E_OBJECTINFO::SHIELD,"실드량 :"},
	{E_OBJECTINFO::SPEED,"속도 :"},{E_OBJECTINFO::CUNSUME_SPEED,"속도 소모량 :"},
	{E_OBJECTINFO::ATTACK_HP_DRAIN,"흡혈량 :"} 
};
extern ObjectInfo GetRandomObjectInfo(int positionNumber, int unitLevel)
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

	int hpValue = floor(percentValue[randomUnitType][0] * upgradeValue);
	int attackValue = floor(percentValue[randomUnitType][1] * upgradeValue);
	int defenceValue = floor(percentValue[randomUnitType][2] * upgradeValue);
	int sheildValue = floor(percentValue[randomUnitType][3] * upgradeValue);
	int speedValue = floor(percentValue[randomUnitType][4] * upgradeValue);
	int consumeValue = floor(percentValue[randomUnitType][5] / upgradeValue);

	newInfoObjext.UpdateBasicInfos(GetDefaultValue(6, hpValue, attackValue, defenceValue, sheildValue, speedValue, consumeValue));
	return newInfoObjext;
}
