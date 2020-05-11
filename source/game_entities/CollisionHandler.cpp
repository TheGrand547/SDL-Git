#include "CollisionHandler.h"
#include "../GameInstance.h"
#include "base/ThingBase.h"

CollisionHandler::CollisionHandler(GameInstance* parent) : parent(parent) {}

CollisionHandler::~CollisionHandler() {}

int CollisionHandler::size() const {
	return this->parent->collisionThings.size();
}

bool CollisionHandler::doesCollideWith(const Rect& rect, void* pointer) const {
	/* True - the rect DOES collide with this collide group
	 * False - the rect DOESN'T collide with this collide group */
	for (std::shared_ptr<ThingBase> thing: this->parent->collisionThings) {
		if (thing.get() != pointer && thing->overlap(rect)) return true;
	}
	return false;
}

bool CollisionHandler::doesNotCollideWith(const Rect& rect, void* pointer) const {
	/* True - the rect DOESN'T collide with this collide group
	 * False - the rect DOES collide with this collide group */
	return !this->doesCollideWith(rect, pointer);
}

bool CollisionHandler::doesCollideWith(const Line& line, void* pointer) const {
	/* True - the line DOES collide with this collide group
	 * False - the line DOESN'T collide with this collide group */
	for (std::shared_ptr<ThingBase> thing : this->parent->collisionThings) {
		if (thing.get() != pointer && thing->doesLineCollide(line)) return true;
	}
	return false;
}

bool CollisionHandler::doesNotCollideWith(const Line& line, void* pointer) const {
	/* True - the line DOESN'T collide with this collide group
	 * False - the line DOES collide with this collide group */
	return !this->doesCollideWith(line, pointer);
}

Point CollisionHandler::closestPointThatCollidesWith(const Line& ray, void* pointer) const {
	Point stored, temp;
	for (std::shared_ptr<ThingBase> thing : this->parent->collisionThings) {
		if (thing.get() == pointer) continue;
		temp = thing->collideLine(ray);
		if (temp.isNull()) continue;
		if (stored.isNull() || temp.distanceToPoint(ray.getOrigin()) < stored.distanceToPoint(ray.getOrigin())) {
			stored = temp;
		}
	}
	return stored;
}



