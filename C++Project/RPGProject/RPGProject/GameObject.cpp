#include "object.h"
void GameActor::RegistNextAction(ObjectAction* nextAction)
{
	//�׼� ��Ϲ�, ���� �׼ǿ� ������ ���׹̳ʰ� ���� ��쿣 �׼� ��� ��� , ����ó�� �߰�
}

void GameActor::ActActions()
{
	for (auto playAction : this->playActionLists) {
		playAction->Action();
	}
	//��� �׼� ������ ����Ʈ Ŭ����ó��
	this->playActionLists.clear();
}
