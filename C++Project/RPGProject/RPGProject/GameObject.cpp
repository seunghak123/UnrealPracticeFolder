#include "object.h"
#include "Managers.h"
void GameActor::RegistNextAction(ObjectAction* nextAction)
{
	this->playActionLists.push_back(nextAction);
}

void GameActor::ActActions()
{
	//�߰��� ���� �ڰ�, �߰��ڿ��� ���� ���� �����ϵ��� ����, �׷��� �ȴٸ� ���� ���İ� ���� ������ �� �� �ִ�.
	for (auto playAction : this->playActionLists) {
		playAction->Action();
	}
	//��� �׼� ������ ����Ʈ Ŭ����ó��
	this->playActionLists.clear();
}
