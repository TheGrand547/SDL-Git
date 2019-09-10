#include "AiProng.h"

AiProng::AiProng(TYPE myType) : myType(myType) {}

AiProng::~AiProng() {}

void AiProng::pathFindTo(EnemyBase* actor) {
	if (actor->parent->nav != NULL) {
		Point center = actor->getCenter();
		if (actor->pathTimer.getTicks() > 250) { // If it has been more than 250 milliseconds since the path has been calculated
			actor->path = NodePath(actor->getClosestUnblockedNode(), actor->parent->getDot()->getPos());
			actor->pathTimer.start();
		}
		if (actor->path.getFirst().isReal()) {
			if (actor->path.getFirst().distanceToPoint(center) < 1.5) { // Make the number a constant
				actor->path.removeLast();
			}
		}
		Point temp = actor->path.getFirst();
		if (temp.isReal()) {
			float angle = atan2(temp.y() - center.y(), temp.x() - center.x());
			actor->move(Vector(angle) * 2.25);
		}
	}
}

void AiProng::execute(EnemyBase* target) {
	switch (this->myType) {
		case TYPE::PATHFIND_TO_TARGET:
			pathFindTo(target);
			break;
	}
}
