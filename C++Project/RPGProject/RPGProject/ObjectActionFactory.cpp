#include "ObjectActionFactory.h"

void ObejctActionFactory::InsertObjectAction(GameActor& actObject, GameActor& targetObject, E_OBJECT_ACTION_TYPE actionType)
{
	ObjectAction* targetAction = nullptr;
	switch (actionType)
	{
	case ATTACK_OTHER:
		targetAction = new AttackAction(&actObject,&targetObject);
		break;
	case MOVE_OTHER:
	case MOVE_SELF:
		targetAction = new MoveAction();
		break;
	case HEAL_OTHER:
		targetAction = new HealAction();
		break;
	case DEFENCE_SELF:
		
		break;
	default:
		//���� ó��
		break;
	}
	if (targetAction == nullptr) {
		//����ó��
		return;
	}
	actObject.RegistNextAction(targetAction);
}
