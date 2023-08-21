#include <string>
#include "UserData.h"

int UserData::GetUserLv() 
{
	int userLv = 1;
	for (int i = 0; i < 20; i++) {
		if (this->userExp < GlobalVariables::userLvExp[i]) {
			userLv = i + 1;
			break;
		}
	}
	
	return userLv; 
}
int UserData::GetUserNextLvEXP() 
{
	int remainExp = 0;
	for (int i = 0; i < 20; i++) {
		if (this->userExp < GlobalVariables::userLvExp[i]) {
			remainExp = GlobalVariables::userLvExp[i] - this->userExp;
			break;
		}
	}

	return remainExp;
}
list<ObjectInfo> UserData::GetUserCardDatas() 
{
	return userCardDatas;
}

void UserData::AddUserCardDatas(GameActor addCardInfo)
{
	this->userCardDatas.push_back(addCardInfo.GetActorObjectInfo());
}
