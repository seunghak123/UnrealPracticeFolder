#include <iostream>
#include <algorithm>
#include <vector>
#include "Object.h"
#include "Managers.h"
#include "ManagerSingleton.h"
#include "SystemInfo.h"
using namespace std;

void main() {
	GameManager::getInstance().InitGame();
}