#pragma once
#include "../../primitives/Rect.h"
#include "../../primitives/Line.h"
#include "ThingBase.h"

/* Base class to handle everything in the world that can collide with other
 * things in the world, such as projectiles, walls, enemies, ect. */
// TODO: Determine if this is deprecated
class CollideBase : public ThingBase {
	public:
		CollideBase();
		virtual ~CollideBase() = 0;
		virtual Point collideLine(const Line& ray) const = 0;
		virtual bool doesLineCollide(const Line& ray) const = 0;
		virtual void draw(SDL_Renderer* renderer, Point offset) = 0;
		virtual Point getTopLeft() const = 0;
		virtual Point getBottomRight() const = 0;
};
