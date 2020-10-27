#include "CollisionHandler.h"
#include "../GameInstance.h"
#include "base/ThingBase.h"
#include "Sector.h"
#include "SectorGroup.h"

CollisionHandler::CollisionHandler(GameInstance* parent) : parent(parent) {}

CollisionHandler::~CollisionHandler() {}

int CollisionHandler::size() const {
	return this->parent->collisionThings.size();
}

bool CollisionHandler::doesCollideWith(const Polygon& rect, const ThingPtr& something) const {
	/* True - the rect DOES collide with this collide group
	 * False - the rect DOESN'T collide with this collide group */
	for (const ThingPtr& thing: this->parent->collisionThings) {
		if (thing.get() != something.get() && thing->overlap(rect)) return true;
	}
	return false;
}

bool CollisionHandler::doesNotCollideWith(const Polygon& rect, const ThingPtr& something) const {
	/* True - the rect DOESN'T collide with this collide group
	 * False - the rect DOES collide with this collide group */
	return !this->doesCollideWith(rect, something);
}

bool CollisionHandler::doesCollideWith(const Line& line, const ThingPtr& something) const {
	/* True - the line DOES collide with this collide group
	 * False - the line DOESN'T collide with this collide group */
	for (const ThingPtr& thing: this->parent->collisionThings) {
		if (thing.get() != something.get() && thing->doesLineCollide(line)) return true;
	}
	return false;
}

bool CollisionHandler::doesNotCollideWith(const Line& line, const ThingPtr& thing) const {
	/* True - the line DOESN'T collide with this collide group
	 * False - the line DOES collide with this collide group */
	return !this->doesCollideWith(line, thing);
}

bool CollisionHandler::doesCollideWith(const ThingPtr& thing) const {
	/* True - the rect DOES collide with this collide group
	 * False - the rect DOESN'T collide with this collide group */
	for (const ThingPtr& ptr: this->parent->collisionThings) {
		if (thing.get() != ptr.get() && thing->overlap(ptr)) return true;
	}
	return false;
}

bool CollisionHandler::doesNotCollideWith(const ThingPtr& thing) const {
	return !this->doesCollideWith(thing);
}

bool CollisionHandler::isPositionOpen(const ThingPtr& thing) {
	for (const ThingPtr& something: this->parent->collisionThings) {
		if (thing.get() != something.get() && something->overlap(thing)) return false;
	}
	return true;
}


Point CollisionHandler::closestPointThatCollidesWith(const Line& ray, const ThingPtr& something) const {
	Point stored, temp;
	for (const ThingPtr& thing: this->parent->collisionThings) {
		if (thing.get() == something.get()) continue;
		temp = thing->collideLine(ray);
		if (temp.isNull()) continue;
		if (stored.isNull() || temp.distanceToPoint(ray.getOrigin()) < stored.distanceToPoint(ray.getOrigin())) {
			stored = temp;
		}
	}
	return stored;
}

void CollisionHandler::finalize() {
	// TODO: Maybe remove?
}


