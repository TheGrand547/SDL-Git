#pragma once
#ifndef THING_BASE_H
#define THING_BASE_H
#include "../../primitives/Point.h"
#include "../../primitives/Rect.h"
#include<memory>
#include<SDL2/SDL.h>
#include<vector>

enum ENTITY_FLAGS {
	SOLID         = 0x0001, // Other objects can collide with this
	NOCLIP        = 0x0002, // This doesn't collide with others
	MOVEABLE      = 0x0004, // This doesn't move
};

class ThingBase {
	protected:
		int flags;
		Point position;
	public:
		virtual ~ThingBase() = 0;
		virtual bool overlap(Rect other) = 0;
		virtual bool overlap(std::shared_ptr<ThingBase>& other) = 0;
		virtual Rect getRect() const = 0;
};
#endif
