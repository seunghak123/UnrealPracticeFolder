#pragma once
#pragma region EnumProperties
#include <map>
#include <string>
//ĳ���� ���ǥ
enum E_RARITY
{
	UNCOMMON,
	COMMON,
	RARE,
	HERO,
	LEGENDARY,
	MYTH,
};
// ĳ���� ���� ����
enum E_OBJECTINFO
{
	//�⺻ ����
	HP,
	ATTACK,
	DEFENCE,
	SHIELD,
	SPEED,
	CUNSUME_SPEED,
	//���� �� ����� ����
	ATTACK_HP_DRAIN,
	INFO_END,
};
//ĳ���� �ൿ ����
enum E_OBJECT_ACTION_TYPE
{
	ATTACK_OTHER,
	MOVE_SELF,
	MOVE_OTHER,
	HEAL_OTHER,
	DEFENCE_SELF,
};
//ĳ���� ���� ����
enum E_STATVALUE_TYPE
{
	ATTACK_VALUE,
	DEFENCE_VALUE,
	HP_VALUE,
	SHIELD_VALUE,
	HP_DRAIN_VALUE,
	CRITICAL_PERCENT_VALUE,
};
//ĳ���� �� ����
enum E_INGAME_TEAM_TYPE
{
	NONE,
	//pvp�� ��
	ALPAH_TEAM,
	BETA_TEAM,
	
	//�δ��� ��
	USER_TEAM,
	MONSTER_TEAM, 
	TEAM_TYPE_END,
};
enum E_INGAME_TYPE
{
	PVP_MODE,
	DUNGEON_MODE,
};
enum E_WEALTH_TYPE
{
	GOLD,
};
enum E_RANDOM_UNIT_TYPE
{
	WARRIOR,
	ARCHER,
	MAGICAN,
};
#pragma endregion EnumProperties
namespace GlobalVariables 
{
#pragma region StaticProperties
	extern const int TEAM_NUMBER_COUNT;
	extern const int TEAM_MIN_NUMBER_COUNT;
	extern const std::map<E_INGAME_TYPE, std::string> INGAME_TYPE_TOSTRING;
#pragma endregion StaticProperties


#pragma region TestConstData
	extern const int userLvExp[20];
	extern const char* EMPTY_STRING ;
#pragma endregion
}
char* GenerateUUID();