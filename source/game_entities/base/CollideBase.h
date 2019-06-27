#pragma once
#include "../../primitives/Rect.h"
#include "../../primitives/Line.h"
#include "../../wrappers/SuperTexture.h"

/* Base class to handle everything in the world that can interat with other
 * things in the world, such as projectiles, walls, enemies, ect.
 * All methods are defined because pure virtual was causing it to be a shitshow
 * but as always, performance > readability > conventions
 * Everything is either a pointer or pass-by-reference to be more efficent */
 
class CollideBase {
	public:
		virtual ~CollideBase() {}
		virtual bool overlap(Rect &other) {
			return false;
		}
		virtual Point collideLine(Line &ray) {
			return Point();
		}
		virtual void draw(SDL_Renderer* renderer, Point offset) {}
		virtual void setTexture(SuperTexture* texture) = 0;
};
