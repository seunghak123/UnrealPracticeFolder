#include "object.h"
void GameActor::RegistNextAction(ObjectAction* nextAction)
{
	this->playActionLists.push_back(nextAction);
}

void GameActor::ActActions()
{
	for (auto playAction : this->playActionLists) {
		playAction->Action();
	}
	//모든 액션 수행후 리스트 클리어처리
	this->playActionLists.clear();
}
