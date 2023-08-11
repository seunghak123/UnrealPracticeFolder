#include "Managers.h"
#include <iostream>

using namespace std;
void TestRenderingManager::ClearConsole()
{
	system("cls");
}
void TestRenderingManager::PrintRenderingText(string renderText)
{
	cout << renderText << endl;
}

void TestRenderingManager::PrintRenderingText(char* renderText)
{
	cout << renderText << endl;
}

void TestRenderingManager::RenderingLobby()
{
	cout << "1.스토리모드" << endl;
	cout << "2.PvP모드" << endl;
	cout << "3.상점" << endl;
}
