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
	void AddUserCardDatas(GameActor addCardInfo);
	int GetUserWealth(E_WEALTH_TYPE wealthType) {
		return userWealth[wealthType];
	}
	bool BuyCard(GameActor buyCardInfo) {
		int buyPrice = buyCardInfo.GetActorObjectInfo().GetBuyPriceValue();
		if (userWealth[E_WEALTH_TYPE::GOLD] - buyPrice > 0) {
			userWealth[E_WEALTH_TYPE::GOLD] -= buyCardInfo.GetActorObjectInfo().GetBuyPriceValue();
			AddUserCardDatas(buyCardInfo);
			return true;
		}
		return false;
	}
	UserData() :userExp(0), userLv(1), userNickName("Empty NickName") {
		userWealth[E_WEALTH_TYPE::GOLD] = 5000;
	}
private:
	string userNickName;
	map<E_WEALTH_TYPE, int> userWealth;
	int userExp;
	int userLv;
	list<ObjectInfo> userCardDatas;
};