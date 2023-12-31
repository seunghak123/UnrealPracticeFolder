#include "object.h"
#include "Managers.h"

void GameActor::ActActions()
{
	//중개자 패턴 박고, 중개자에서 실제 내용 실행하도록 변경, 그렇게 된다면 순서 정렬과 같은 내용을 할 수 있다.
	for (auto& playAction : playActionLists) {
		playAction->Action();
	}
	//모든 액션 수행후 리스트 클리어처리
	this->playActionLists.clear();
}
