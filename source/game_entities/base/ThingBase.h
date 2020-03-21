#pragma once
#ifndef THING_BASE_H
#define THING_BASE_H
class ThingBase;
class GameInstance;
#include "../../GameInstance.h"
#include "../../primitives/Point.h"
#include "../../primitives/Rect.h"
#include<memory>
#include<SDL2/SDL.h>
#include<vector>

enum ENTITY_FLAG {
	SOLID                   = 0x0001, // Other objects can collide with this at some point
	NOCLIP                  = 0x0002, // This doesn't collide with others
	MOVEABLE                = 0x0004, // This object can move
	DRAW                    = 0x0008, // This object can be drawn
	BLOCKS_VISIBILTY        = 0x0010  // This object can block visibility
};

enum ENTITY_DIRECTION {
	RIGHT, UP_RIGHT, UP, UP_LEFT, LEFT, DOWN_LEFT, DOWN, DOWN_RIGHT
};

ENTITY_DIRECTION getDirectionFromAngle(const double angle);

class ThingBase {
	protected:
		GameInstance* parent;
		const int absoluteFlags; // List of attributes this object /can/ have, but might not necessarily have at any given moment
		int flags; // List of attributes the object CURRENTLY has
		Point position;
	public:
		ThingBase(int flags = 0);
		virtual ~ThingBase() = 0;
		virtual bool doesLineCollide(const Line& ray) const = 0;
		/* overlap(Rect) -> Does /this/ collide with that specific rectangle
		 * overlap(shared_ptr<Thing>) -> Does this object collide with this object(ie call the objects 
		 * 		overlap with each hitbox in this */ 
		 // TODO: Make a HitBox class
		virtual bool overlap(const Rect& other) const = 0;
		virtual bool overlap(const std::shared_ptr<ThingBase>& other) const = 0;
		int getAbsoluteFlags() const;
		int getFlags() const;
		virtual double originDistance() const = 0;
		virtual Point collideLine(const Line& ray) const = 0;
		virtual Point getPosition() const = 0;
		virtual Rect getRect() const = 0;
		virtual void addNodes();
		virtual void draw(SDL_Renderer* renderer, Point offset = Point(0, 0)) = 0;
		void setFlag(ENTITY_FLAG flag);
		void setParent(GameInstance* parent);
		void unsetFlag(ENTITY_FLAG flag);
		virtual void update() = 0;
};
#endif
