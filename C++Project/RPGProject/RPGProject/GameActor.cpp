#include "object.h"
#include "Managers.h"

void GameActor::ActActions()
{
	//�߰��� ���� �ڰ�, �߰��ڿ��� ���� ���� �����ϵ��� ����, �׷��� �ȴٸ� ���� ���İ� ���� ������ �� �� �ִ�.
	for (auto& playAction : playActionLists) {
		playAction->Action();
	}
	//��� �׼� ������ ����Ʈ Ŭ����ó��
	this->playActionLists.clear();
}
