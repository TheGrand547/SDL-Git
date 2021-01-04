#include "CollisionHandler.h"
#include "base/ThingBase.h"
#include "Sector.h"
#include "SectorGroup.h"

CollisionHandler::CollisionHandler() {}

bool CollisionHandler::locationValid(const ThingPtr& source, const int& flags) {
	for (const ThingPtr& something: CollisionHandler::parent->collisionThings) {
		if (source.get() != something.get() && something->overlap(source, flags)) return false;
	}
	return true;
}

int CollisionHandler::size() {
	return CollisionHandler::parent->collisionThings.size();
}

Point CollisionHandler::closestPointThatCollidesWith(const ThingPtr& source, const Line& ray) {
	Point stored, temp;
	for (const ThingPtr& thing: CollisionHandler::parent->collisionThings) {
		if (thing.get() == source.get()) continue;
		temp = thing->collideLine(ray);
		if (temp.isNull()) continue;
		if (stored.isNull() || temp.distanceToPoint(ray.getOrigin()) < stored.distanceToPoint(ray.getOrigin())) {
			stored = temp;
		}
	}
	return stored;
}

void CollisionHandler::setTarget(GameInstance* parent) {
	if (parent) CollisionHandler::parent = parent;
}
