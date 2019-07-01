#pragma once
#include "../../primitives/Rect.h"
#include "../../primitives/Line.h"
#include "../../wrappers/SuperTexture.h"

/* Base class to handle everything in the world that can collide with other
 * things in the world, such as projectiles, walls, enemies, ect.
 * Everything is either a pointer or pass-by-reference to be more efficent */
 
class CollideBase {
	public:
		virtual ~CollideBase() {}
		virtual bool overlap(Rect& other) = 0;
		virtual Point collideLine(Line& ray) = 0;
		virtual void draw(SDL_Renderer* renderer, Point offset) = 0;
		virtual void setTexture(SuperTexture* texture) = 0;
};
