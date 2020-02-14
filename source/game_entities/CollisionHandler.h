#pragma once
#ifndef COLLISION_HANDLER_H
#define COLLISION_HANDLER_H
class CollisionHandler;
class GameInstance;
#include "../primitives/Line.h"
#include "../primitives/Rect.h"
#include<memory>
#include<vector>

// Interface to interact with the collidable objects from GameInstance
class CollisionHandler {
	private:
		GameInstance* parent;
	public:
		CollisionHandler(GameInstance* parent);
		~CollisionHandler();
		int size() const;
		bool doesCollideWith(const Rect rect) const;
		bool doesCollideWith(const Line ray) const;
		bool doesNotCollideWith(const Rect rect) const;
		bool doesNotCollideWith(const Line line) const;
		Point closestPointThatCollidesWith(const Line ray) const;
};

#endif
