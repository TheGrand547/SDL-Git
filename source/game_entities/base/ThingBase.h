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

enum ENTITY_FLAGS {
	SOLID                   = 0x0001, // Other objects can collide with this at some point
	NOCLIP                  = 0x0002, // This doesn't collide with others
	MOVEABLE                = 0x0004, // This object can move
	DRAW                    = 0x0008, // This object can be drawn
	BLOCKS_VISIBILTY        = 0x0010  // This object can block visibility
};

class ThingBase {
	protected:
		GameInstance* parent;
		int flags;
		Point position;
	public:
		virtual ~ThingBase() = 0;
		virtual bool doesLineCollide(const Line& ray) const = 0;
		
		/* overlap(Rect) -> Does /this/ collide with that specific rectangle
		 * overlap(shared_ptr<Thing>) -> Does this object collide with this object(ie call the objects 
		 * 		overlap with each hitbox in this */ 
		 // TODO: Make a HitBox class
		virtual bool overlap(const Rect& other) const = 0;
		virtual bool overlap(const std::shared_ptr<ThingBase>& other) const = 0;
		int getFlags() const;
		virtual float originDistance() const = 0;
		virtual Point collideLine(const Line& ray) const = 0;
		virtual Point getPosition() const = 0;
		virtual Rect getRect() const = 0;
		virtual void addNodes();
		virtual void draw(SDL_Renderer* renderer, Point offset = Point(0, 0)) = 0;
		void setParent(GameInstance* parent);
		virtual void update() = 0;
};
#endif
