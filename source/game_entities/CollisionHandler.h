#pragma once
#ifndef COLLISION_HANDLER_H
#define COLLISION_HANDLER_H
class GameInstance;
class CollisionHandler;
class ThingBase;
class SectorBase;
#include "../primitives/Line.h"
#include "../primitives/Polygon.h"
#include<map>
#include<memory>
#include<vector>

// Interface to interact with the collidable objects from GameInstance
class CollisionHandler {
	public:
		GameInstance* parent;
		CollisionHandler(GameInstance* parent);
		~CollisionHandler();
		int size() const;
		bool doesCollideWith(const Polygon& rect, void* pointer = NULL) const;
		bool doesCollideWith(const Line& ray, void* pointer = NULL) const;
		bool doesCollideWith(const std::shared_ptr<ThingBase>& thing) const;
		bool doesNotCollideWith(const Polygon& rect, void* pointer = NULL) const;
		bool doesNotCollideWith(const std::shared_ptr<ThingBase>& thing) const;
		bool doesNotCollideWith(const Line& line, void* pointer = NULL) const;
		Point closestPointThatCollidesWith(const Line& ray, void* pointer = NULL) const;
};

#endif
