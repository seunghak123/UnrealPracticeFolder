#pragma once
#include "ManagerSingleton.h"
class GameManager : public ManagerSingleton < GameManager> 
{
public:
	int a = 10;
	void TestPrint();
};