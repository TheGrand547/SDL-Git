#pragma once
#include "Rect.h"
#include "primatives/Line.h"
/*
 * Base class to handle everything in the world that can interat with other
 * things in the world, such as projectiles, walls, enemies, ect.
 * All methods are pure virtual as there is no catch all default due to the differences 
 * in implementations.
 * Everything is either a pointer or pass-by-reference to be more efficent
 */

class CollideBase{
	public:
		virtual bool overlap(Rect &other) = 0; 
		virtual Point collideLine(Line &ray) = 0;
		virtual void draw(SDL_Renderer* renderer) = 0;
};
