#pragma once
#include "Rect.h"
#include "primatives/Line.h"
/*
 * Base class to handle everything in the world that can interat with other
 * things in the world, such as projectiles, walls, enemies, ect.
 * All methods are defined because pure virtual was causing it to be a shitshow
 * but as always, performance > readability > conventions
 * Everything is either a pointer or pass-by-reference to be more efficent
 */
class CollideBase{
	public:
		bool overlap(Rect &other) {
			return false;
		}
		
		Point collideLine(Line &ray) {
			return Point();
		}
		
		void draw(SDL_Renderer* renderer) {}
};
