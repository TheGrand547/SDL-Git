#pragma once
#ifndef COLLISION_HANDLER_H
#define COLLISION_HANDLER_H

class GameInstance;
class CollisionHandler;
class ThingBase;

#include "../primitives/Line.h"
#include "../primitives/Polygon.h"
#include <map>
#include <memory>
#include <vector>

typedef std::shared_ptr<ThingBase> ThingPtr;
typedef std::weak_ptr<ThingBase> WeakThingPtr;
typedef std::vector<WeakThingPtr> WeakThingVector;

// Interface to interact with the collidable objects from GameInstance
class CollisionHandler {
	protected:
		friend class GameInstance;
	public:
		GameInstance* parent;
		CollisionHandler(GameInstance* parent);
		~CollisionHandler();
		int size() const;
		bool isPositionOpen(const std::shared_ptr<ThingBase>& thing);
		bool doesCollideWith(const Polygon& rect, const ThingPtr& something = NULL) const;
		bool doesCollideWith(const Line& ray, const ThingPtr& something = NULL) const;
		bool doesCollideWith(const ThingPtr& thing) const;
		bool doesNotCollideWith(const Polygon& rect, const ThingPtr& something = NULL) const;
		bool doesNotCollideWith(const ThingPtr& thing) const;
		bool doesNotCollideWith(const Line& line, const ThingPtr& something = NULL) const;
		Point closestPointThatCollidesWith(const Line& ray, const ThingPtr& something = NULL) const;
		void finalize();
};
#endif
