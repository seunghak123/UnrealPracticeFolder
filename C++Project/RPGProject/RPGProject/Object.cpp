#include "Object.h"
#include "SystemInfo.h"
#include <iostream>
#include "Managers.h"

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

	TestRenderingManager::PrintRenderingText("데미지 부여");
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