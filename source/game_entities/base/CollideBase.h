#pragma once
#include "../../primitives/Rect.h"
#include "../../primitives/Line.h"
#include "ThingBase.h"

/* Base class to handle everything in the world that can collide with other
 * things in the world, such as projectiles, walls, enemies, ect. */
class CollideBase : public ThingBase {
	public:
		CollideBase();
		virtual ~CollideBase() = 0;
		virtual Point collideLine(Line& ray) = 0;
		virtual bool doesLineCollide(Line& ray) = 0;
		virtual void draw(SDL_Renderer* renderer, Point offset) = 0;
		virtual Point getTopLeft() = 0;
		virtual Point getBottomRight() = 0;
};
