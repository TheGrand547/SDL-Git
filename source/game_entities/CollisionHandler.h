#pragma once
#ifndef COLLISION_HANDLER_H
#define COLLISION_HANDLER_H

class ThingBase;

#include "../primitives/Line.h"
#include "../primitives/Polygon.h"
#include "../GameInstance.h"
#include <map>
#include <memory>
#include <vector>

typedef std::shared_ptr<ThingBase> ThingPtr;
typedef std::weak_ptr<ThingBase> WeakThingPtr;
typedef std::vector<WeakThingPtr> WeakThingVector;

// Interface to interact with the collidable objects from GameInstance
class _CollisionHandler {
	protected:
		friend class GameInstance;
	public:
		GameInstance* parent;
		_CollisionHandler(GameInstance* parent);
		~_CollisionHandler();

		// TODO: Probably deprecated
		bool isPositionOpen(const ThingPtr& thing);
		bool doesCollideWith(const Polygon& rect, const ThingPtr& something = NULL) const;
		bool doesCollideWith(const Line& ray, const ThingPtr& something = NULL) const;
		bool doesCollideWith(const ThingPtr& thing) const;

		bool doesNotCollideWith(const Polygon& rect, const ThingPtr& something = NULL) const;
		bool doesNotCollideWith(const ThingPtr& thing) const;
		bool doesNotCollideWith(const Line& line, const ThingPtr& something = NULL) const;

		// Modern!
		template<typename T> bool overlapTest(const ThingPtr& source, const T&& collide, const int& flags);

		int size() const;
		Point closestPointThatCollidesWith(const Line& ray, const ThingPtr& something = NULL) const;
};

template<typename T> bool _CollisionHandler::overlapTest(const ThingPtr& source, const T&& collide, const int& flags) {
	for (const ThingPtr& something: this->parent->collisionThings) {
		if (source.get() != something.get() && something->overlap(std::forward(collide), flags)) return false;
	}
	return true;
}
#endif
