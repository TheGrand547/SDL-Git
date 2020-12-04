#pragma once
#ifndef THING_BASE_H
#define THING_BASE_H
#include "../../essential/SDL_Headers.h"
#include "../../primitives/Point.h"
#include "../../primitives/Polygon.h"
#include "../../primitives/Rect.h"
#include <memory>
#include <SDL.h>
#include <vector>

class GameInstance;
class ThingBase;

typedef std::shared_ptr<ThingBase> ThingPtr;

enum ENTITY_FLAG {
	SOLID                   = 0x0001, // Other objects can collide with this at some point
	NOCLIP                  = 0x0002, // This doesn't collide with others
	MOVEABLE                = 0x0004, // This object can move
	DRAW                    = 0x0008, // This object can be drawn
	BLOCKS_VISIBILTY        = 0x0010, // This object can block visibility
};

enum ENTITY_DIRECTION {
	RIGHT, UP_RIGHT, UP, UP_LEFT, LEFT, DOWN_LEFT, DOWN, DOWN_RIGHT
};

double getAngleFromDirection(const ENTITY_DIRECTION& direction);
ENTITY_DIRECTION getDirectionFromAngle(double angle);

class ThingBase : public std::enable_shared_from_this<ThingBase> {
	protected:
		double angle;
		const int absoluteFlags; // List of attributes this object CAN have, but might not necessarily have at any given moment
		int flags; // List of attributes the object CURRENTLY has
		Point position;
		std::vector<ThingPtr> myThings;
		ThingBase* owner; // For whatever you need to have it do
		const std::size_t hashValue;
		virtual void pingInternal([[maybe_unused]] const std::string& info = "", [[maybe_unused]] const double& data = 0.0);
	public:
		GameInstance* parent;

		ThingBase(int flags = 0);
		virtual ~ThingBase() = 0;
		virtual bool doesLineCollide(const Line& ray) const = 0;
		virtual bool isAlive() const;
		/* overlap(Polygon) -> Does /this/ collide with that specific polygon
		 * overlap(shared_ptr<Thing>) -> Does this object collide with this object(ie call the objects 
		 * 		overlap with each hitbox in this */ 
		virtual bool overlap(const Polygon& other) const = 0;
		virtual bool overlap(const ThingPtr& other) const = 0;
		virtual double originDistance() const = 0;
		virtual Point collideLine(const Line& ray) const = 0;
		virtual Point getPosition() const = 0;
		virtual Rect getBoundingRect() const = 0;
		virtual std::size_t hash() const;
		virtual std::vector<ThingPtr>& getMyThings();
		virtual void draw() = 0;
		virtual void update();
		double getAngle() const;
		int getAbsoluteFlags() const;
		int getFlags() const;
		void ping(const std::string& info = "", const double& data = 0.0);
		void setAngle(const Point& point);
		void setFlag(ENTITY_FLAG flag);
		void setOwner(ThingBase* ptr);
		void setParent(GameInstance* parent);
		void unsetFlag(ENTITY_FLAG flag);
		//template<typename T, typename... Args> std::shared_ptr<T> createOwnedThing(Args&&... args);
};

namespace std {
	template<> struct hash<ThingPtr> {
		std::size_t operator()(const ThingPtr& thing) const noexcept;
	};
}
// TODO: Figure out how to do this without creating a nightmare
/*
template<typename T, typename... Args> std::shared_ptr<T> ThingBase::createOwnedThing(Args&&... args) {
	static_assert(std::is_base_of<ThingBase, T>::value, "createOwnedThing must be templated with a class that derives from ThingBase.");
	std::shared_ptr<T> thing = this->parent->createThing<T>(std::forward<Args>(args)...);
	this->myThings.push_back(thing);
	thing->setOwner(this);
	return thing;
}*/
#endif
