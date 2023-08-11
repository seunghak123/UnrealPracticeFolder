#pragma once
#pragma region EnumProperties
//캐릭터 등급표
enum E_RARITY
{
	UNCOMMON,
	COMMON,
	RARE,
	HERO,
	LEGENDARY,
	MYTH,
};
// 캐릭터 스탯 종류
enum E_OBJECTINFO
{
	//기본 스탯
	HP,
	ATTACK,
	DEFENCE,
	SHIELD,
	SPEED,
	CUNSUME_SPEED,
	//버프 및 디버프 스탯
	ATTACK_HP_DRAIN,

};
//캐릭터 행동 종류
enum E_OBJECT_ACTION_TYPE
{
	ATTACK_OTHER,
	MOVE_SELF,
	MOVE_OTHER,
	HEAL_OTHER,
	DEFENCE_SELF,
};
//캐릭터 스탯 종류
enum E_STATVALUE_TYPE
{
	ATTACK_VALUE,
	DEFENCE_VALUE,
	HP_VALUE,
	SHIELD_VALUE,
	HP_DRAIN_VALUE,
	CRITICAL_PERCENT_VALUE,
};
//캐릭터 팀 종류
enum E_INGAME_TEAM_TYPE
{
	NONE,
	//pvp용 팀
	ALPAH_TEAM,
	BETA_TEAM,
	
	//인던용 팀
	USER_TEAM,
	MONSTER_TEAM, 
	END
};
enum E_INGAME_TYPE
{
	PVP_MODE,
	DUNGEON_MODE,
};
#pragma endregion EnumProperties
#pragma region StaticProperties
const int TEAM_NUMBER_COUNT = 3;
const int TEAM_MIN_NUMBER_COUNT = 1;
#pragma endregion StaticProperties