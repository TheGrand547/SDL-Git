#include "CollisionHandler.h"

CollisionHandler::CollisionHandler(GameInstance* parent) : parent(parent) {}

CollisionHandler::~CollisionHandler() {}

int CollisionHandler::size() const {
	return this->parent->collision.size();
}

bool CollisionHandler::doesCollideWith(Rect rect) {
	/* True - the rect DOES collide with this collide group
	 * False - the rect DOESN'T collide with this collide group */
	bool result = false;
	for (std::shared_ptr<ThingBase> thing: this->parent->collisionThings) {
		result = thing->overlap(rect);
		if (result) {
			break;
		}
	}
	return result;
}

bool CollisionHandler::doesNotCollideWith(Rect rect) {
	/* True - the rect DOESN'T collide with this collide group
	 * False - the rect DOES collide with this collide group */
	bool result = false;
	for (std::shared_ptr<ThingBase> thing: this->parent->collisionThings) {
		result = thing->overlap(rect);
		if (result) {
			break;
		}
	}
	return !result;
}

bool CollisionHandler::doesCollideWith(Line line) {
	return false;
}

bool CollisionHandler::doesNotCollideWith(Line line) {
	return true;
}
