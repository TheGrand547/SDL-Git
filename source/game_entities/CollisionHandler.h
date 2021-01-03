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
class CollisionHandler {
	protected:
		inline static GameInstance* parent;
	public:
		static bool locationValid(const ThingPtr& source, const int& flags = OVERLAP_TYPE::DEFAULT);
		// Modern!
		template<typename T> static bool overlapTest(const ThingPtr& source, const T& collide, const int& flags = OVERLAP_TYPE::DEFAULT);
		//template<typename T> static Point intersection(const ThingPtr& source, const T&& collide, const int& flags);
		static int size();
		// TODO: Add flags
		static Point closestPointThatCollidesWith(const ThingPtr& source, const Line& ray);
		static void setTarget(GameInstance* parent);
};

template<typename T> bool CollisionHandler::overlapTest(const ThingPtr& source, const T& collide, const int& flags) {
	for (const ThingPtr& something: CollisionHandler::parent->collisionThings) {
		if (source.get() != something.get() && something->overlap(collide, flags)) return false;
	}
	return true;
}
/*
template<typename T> bool CollisionHandler::overlapTest(const ThingPtr& source, const T&& collide, const int& flags) {
	Point value;
	for (const ThingPtr& something: this->parent->collisionThings) {
		if (source.get() != something.get() && something->overlap(std::forward(collide), flags)) return false;
	}
	return value;
}*/
#endif
