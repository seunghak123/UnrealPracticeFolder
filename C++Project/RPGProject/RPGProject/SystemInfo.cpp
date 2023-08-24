#include "SystemInfo.h"
#include <time.h>
#include "Object.h"
namespace GlobalVariables
{
#pragma region StaticProperties
	const int TEAM_NUMBER_COUNT = 3;
	const int TEAM_MIN_NUMBER_COUNT = 1;
#pragma endregion StaticProperties

	const std::map<E_INGAME_TYPE, std::string> INGAME_TYPE_TOSTRING = {
			{E_INGAME_TYPE::DUNGEON_MODE,"스토리 모드"},{E_INGAME_TYPE::PVP_MODE,"유저대전 모드"},
	};
#pragma region TestConstData
	const int USER_LEVEL_EXP[20] = { 0,100,200,400,800,1600,3200,6400,12800,25600,
								   51200,102400,204800,409600,819200,
								   1638400,3276800,6553600,13172000,2000000000 };
	const int STORY_MONSTER_COUNT[10] = { 1,1,2,2,2,3,3,4,5,6 };
	const char* EMPTY_STRING = "Empty NickName";
	const int MAX_STORYMODE_LEVEL = 10;
#pragma endregion
}
int changeValue = 0;
char* GenerateUUID()
{
	int t = 0;
	const char* szTemp = "xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx";
	const char* szHex = "0123456789abcdef-";
	int nLen = strlen(szTemp);
	char* pUUID = new char[nLen];
	srand(clock() + changeValue);
	changeValue++;
	for (t = 0; t < nLen; t++)
	{
		int r = rand() % 16;
		char c = ' ';
		switch (szTemp[t])
		{
		case 'x':
			c = szHex[r];
			break;
		case 'y':
			c = szHex[r & 0x03 | 0x08];
			break;
		case '-':
			c = '-';
			break;
		case '4':
			c = '4';
			break;
		default:
			break;
		}
		pUUID[t] = c;
	}
	pUUID[t] = 0;
	return pUUID;
}