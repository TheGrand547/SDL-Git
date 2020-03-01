#include "CollisionHandler.h"
#include "../GameInstance.h"
#include "base/ThingBase.h"

CollisionHandler::CollisionHandler(GameInstance* parent) : parent(parent) {}

CollisionHandler::~CollisionHandler() {}

int CollisionHandler::size() const {
	return this->parent->collisionThings.size();
}

bool CollisionHandler::doesCollideWith(const Rect& rect) const {
	/* True - the rect DOES collide with this collide group
	 * False - the rect DOESN'T collide with this collide group */
	for (std::shared_ptr<ThingBase> thing: this->parent->collisionThings) {
		if (thing->overlap(rect)) return true;
	}
	return false;
}

bool CollisionHandler::doesNotCollideWith(const Rect& rect) const {
	/* True - the rect DOESN'T collide with this collide group
	 * False - the rect DOES collide with this collide group */
	return !this->doesCollideWith(rect);
}

bool CollisionHandler::doesCollideWith(const Line& line) const {
	/* True - the line DOES collide with this collide group
	 * False - the line DOESN'T collide with this collide group */
	for (std::shared_ptr<ThingBase> thing : this->parent->collisionThings) {
		if (thing->doesLineCollide(line)) return true;
	}
	return false;
}

bool CollisionHandler::doesNotCollideWith(const Line& line) const {
	/* True - the line DOESN'T collide with this collide group
	 * False - the line DOES collide with this collide group */
	return !this->doesCollideWith(line);
}

Point CollisionHandler::closestPointThatCollidesWith(const Line& ray) const {
	Point stored, temp;
	for (std::shared_ptr<ThingBase> thing : this->parent->collisionThings) {
		temp = thing->collideLine(ray);
		if (stored.isNull() || temp.distanceToPoint(ray.getOrigin()) < stored.distanceToPoint(ray.getOrigin())) {
			stored = temp;
		}
	}
	return stored;
}



