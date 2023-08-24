#include <string>
#include "UserData.h"
#include <vector>
int UserData::GetUserLv() 
{
	int userLv = 1;
	for (int i = 0; i < 20; i++) {
		if (this->userExp < GlobalVariables::USER_LEVEL_EXP[i]) {
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
		if (this->userExp < GlobalVariables::USER_LEVEL_EXP[i]) {
			remainExp = GlobalVariables::USER_LEVEL_EXP[i] - this->userExp;
			break;
		}
	}

	return remainExp;
}
list<ObjectInfo> UserData::GetUserCardDatas() 
{
	return userCardDatas;
}

void UserData::AddUserCardDatas(GameActor& addCardInfo)
{
	this->userCardDatas.push_back(addCardInfo.GetActorObjectInfo());
}

tuple<vector<GameActor> ,int> UserData::GetUserCardLists()
{
	vector<GameActor> userCardArray;
	int index = 0;
	for (auto cardinfo : this->userCardDatas) 
	{
		userCardArray.push_back( *(new GameActor(cardinfo)));
	}

	return make_tuple(userCardArray, this->userCardDatas.size());
}
