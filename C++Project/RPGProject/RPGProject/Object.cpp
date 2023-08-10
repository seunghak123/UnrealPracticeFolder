#include "Object.h"
#include "SystemInfo.h"
#include <iostream>

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
bool ObjectInfo::HasInfoValue(E_OBJECTINFO infoType)
{
	auto it = this->objectInfo.find(infoType);
	if (it == this->objectInfo.end()) {
		return false;
	}

	return true;
}
#if Test_Code
void ObjectInfo::PrintValues()
{
	for (const auto& pair : this->objectInfo) {
		std::cout << "Key: " << (E_OBJECTINFO)pair.first << " Value: " << pair.second << std::endl;
	}
}
#endif // Test_Code
#pragma region  ActionFuction
void ObjectAction::Action()
{
}
#pragma region AttackAtion
void AttackAction::Action() 
{

}
void AttackAction::ActionWork(DamageStruct damageStruct)
{
	ObjectInfo targetObjectInfo = damageStruct.targetActor->GetActorObjectInfo();

	//damageStruct를 이용해서 데미지 계산 및 데미지 부여
	//targetObjectInfo.
	//attackType
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
#pragma endregion HealAction
#pragma endregion ActionFuction

ObjectInfo& GameActor::GetActorObjectInfo()
{
	return this->objectInfo;
}
