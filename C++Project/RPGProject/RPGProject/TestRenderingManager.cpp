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
	cout << "1.���丮���" << endl;
	cout << "2.PvP���" << endl;
	cout << "3.����" << endl;
}
