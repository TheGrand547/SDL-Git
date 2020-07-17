#pragma once
#ifndef THING_BASE_H
#define THING_BASE_H
class ThingBase;
class GameInstance;
#include "../../primitives/Point.h"
#include "../../primitives/Polygon.h"
#include "../../primitives/Rect.h"
#include<memory>
#include<SDL2/SDL.h>
#include<vector>

enum ENTITY_FLAG {
	SOLID                   = 0x0001, // Other objects can collide with this at some point
	NOCLIP                  = 0x0002, // This doesn't collide with others
	MOVEABLE                = 0x0004, // This object can move
	DRAW                    = 0x0008, // This object can be drawn
	BLOCKS_VISIBILTY        = 0x0010, // This object can block visibility
	PLAYER_ALLY             = 0x0020, // This object should not interact with player created damage zones, and should interact with non player damage zones
	HAS_EFFECT_ZONES        = 0x0040  // This object might have zones that interact with other things
};

enum ENTITY_DIRECTION {
	RIGHT, UP_RIGHT, UP, UP_LEFT, LEFT, DOWN_LEFT, DOWN, DOWN_RIGHT
};

ENTITY_DIRECTION getDirectionFromAngle(const double angle);

class ThingBase : public std::enable_shared_from_this<ThingBase> {
	protected:
		const int absoluteFlags; // List of attributes this object CAN have, but might not necessarily have at any given moment
		int flags; // List of attributes the object CURRENTLY has
		Point position;
		std::vector<std::weak_ptr<ThingBase>> attached;
	public:
		GameInstance* parent;
	
		ThingBase(int flags = 0);
		virtual ~ThingBase() = 0;
		virtual bool doesLineCollide(const Line& ray) const = 0;
		/* overlap(Rect) -> Does /this/ collide with that specific rectangle
		 * overlap(shared_ptr<Thing>) -> Does this object collide with this object(ie call the objects 
		 * 		overlap with each hitbox in this */ 
		virtual bool overlap(const Polygon& other) const = 0;
		virtual bool overlap(const std::shared_ptr<ThingBase>& other) const = 0;
		virtual bool wideOverlap(const Polygon& other) const = 0; // TODO: get rid of this fucking bullshit
		int getAbsoluteFlags() const;
		int getFlags() const;
		virtual double originDistance() const = 0;
		virtual Point collideLine(const Line& ray) const = 0;
		virtual Point getPosition() const = 0;
		virtual Rect getBoundingRect() const = 0;
		virtual void draw(SDL_Renderer* renderer, Point offset = Point(0, 0)) = 0;
		virtual void update();
		void setFlag(ENTITY_FLAG flag);
		void setParent(GameInstance* parent);
		void unsetFlag(ENTITY_FLAG flag);
};
#endif
