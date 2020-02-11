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
		bool doesCollideWith(Rect rect);
		bool doesCollideWith(Line ray);
		bool doesNotCollideWith(Rect rect);
		bool doesNotCollideWith(Line line);
		bool doesPlayerNotCollide(Rect rect);
		Point closestPointThatCollidesWith(Line ray);
};

#endif
