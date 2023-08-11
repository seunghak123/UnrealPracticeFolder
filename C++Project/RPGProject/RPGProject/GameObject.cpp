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
	//��� �׼� ������ ����Ʈ Ŭ����ó��
	this->playActionLists.clear();
}
