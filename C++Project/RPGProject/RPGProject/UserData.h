#pragma once
#include <string>
#include <map>
#include <list>
#include "SystemInfo.h"
#include "Object.h"
#include <vector>
using namespace std;


class UserData
{
public:
	int GetUserLv();
	int GetUserNextLvEXP();
	list<ObjectInfo> GetUserCardDatas();
	void AddUserCardDatas(GameActor& addCardInfo);
	tuple<std::vector<GameActor>, int> GetUserCardLists();
	int GetUserWealth(E_WEALTH_TYPE wealthType) {
		return userWealth[wealthType];
	}
	bool BuyCard(GameActor&& buyCardInfo) {
		int buyPrice = buyCardInfo.GetActorObjectInfo().GetBuyPriceValue();
		if (userWealth[E_WEALTH_TYPE::GOLD] - buyPrice > 0) {
			userWealth[E_WEALTH_TYPE::GOLD] -= buyCardInfo.GetActorObjectInfo().GetBuyPriceValue();
			AddUserCardDatas(buyCardInfo);
			return true;
		}
		return false;
	}
	bool SellCard(GameActor* sellCardInfo)
	{
		ObjectInfo targetInfo = sellCardInfo->GetActorObjectInfo();
		if (HasCardDatas(targetInfo)) {
			int sellPrice = sellCardInfo->GetActorObjectInfo().GetSellPriceValue();
			userWealth[E_WEALTH_TYPE::GOLD] += targetInfo.GetSellPriceValue();
			RemoveUserCardDatas(targetInfo);
			return true;
		}
	}
	bool HasCardDatas(ObjectInfo targetInfo) 
	{
		if (find_if(userCardDatas.begin(), userCardDatas.end(),
			[&targetInfo](ObjectInfo& findTarget) {
				return findTarget.GetUniqueId() == targetInfo.GetUniqueId();
			}) != userCardDatas.end()) {
			return true;
		}
		return false;
	}
	void RemoveUserCardDatas(ObjectInfo targetObject)
	{
		userCardDatas.erase(remove_if(userCardDatas.begin(), userCardDatas.end(), [&targetObject](ObjectInfo& findTarget) {
			return findTarget.GetUniqueId() == targetObject.GetUniqueId();
			}), userCardDatas.end());
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
	list<string> currentDeck;
};