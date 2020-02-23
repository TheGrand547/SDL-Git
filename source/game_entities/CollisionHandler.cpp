#include "CollisionHandler.h"
#include "../GameInstance.h"
#include "base/ThingBase.h"

CollisionHandler::CollisionHandler(GameInstance* parent) : parent(parent) {}

CollisionHandler::~CollisionHandler() {}

int CollisionHandler::size() const {
	return this->parent->collisionThings.size();
}

bool CollisionHandler::doesCollideWith(const Rect rect) const {
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

bool CollisionHandler::doesNotCollideWith(const Rect rect) const {
	/* True - the rect DOESN'T collide with this collide group
	 * False - the rect DOES collide with this collide group */
	return !this->doesCollideWith(rect);
}

bool CollisionHandler::doesCollideWith(const Line line) const {
	/* True - the line DOES collide with this collide group
	 * False - the line DOESN'T collide with this collide group */
	bool result = false;
	for (std::shared_ptr<ThingBase> thing : this->parent->collisionThings) {
		result = thing->doesLineCollide(line);
		if (result) break;
	}
	return result;
}

bool CollisionHandler::doesNotCollideWith(const Line line) const {
	/* True - the line DOESN'T collide with this collide group
	 * False - the line DOES collide with this collide group */
	return !this->doesCollideWith(line);
}

Point CollisionHandler::closestPointThatCollidesWith(const Line ray) const {
	Point stored;
	for (std::shared_ptr<ThingBase> thing : this->parent->collisionThings) {
		stored = smallerDistance(ray.getOrigin(), thing->collideLine(ray), stored);
	}
	return stored;
}



