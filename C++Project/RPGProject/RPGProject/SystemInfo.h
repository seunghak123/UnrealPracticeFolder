#pragma once
#pragma region EnumProperties
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