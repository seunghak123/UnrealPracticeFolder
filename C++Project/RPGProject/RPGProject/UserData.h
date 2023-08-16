#pragma once
#include <string>
#include <map>
#include <list>
#include "SystemInfo.h"
#include "Object.h"
using namespace std;


class UserData
{
public:
	int GetUserLv();
	int GetUserNextLvEXP();
	list<ObjectInfo> GetUserCardDatas();
private:
	string userNickName;
	map<E_WEALTH_TYPE, int> userWealth;
	int userExp;
	int userLv;
	list<ObjectInfo> userCardDatas;
};