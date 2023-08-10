#include "object.h"
void GameActor::RegistNextAction(ObjectAction* nextAction)
{
	//액션 등록및, 다음 액션에 수행할 스테미너가 없을 경우엔 액션 등록 취소 , 예외처리 추가
}

void GameActor::ActActions()
{
	for (auto playAction : this->playActionLists) {
		playAction->Action();
	}
	//모든 액션 수행후 리스트 클리어처리
	this->playActionLists.clear();
}
