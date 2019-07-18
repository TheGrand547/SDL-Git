#pragma once
#ifndef DRAW_GROUP_H
#define DRAW_GROUP_H
#include<SDL2/SDL.h>
#include "../BoundedPoint.h"
#include "../essential/MegaBase.h"
/* Base class for the various lists of entities or "things" that need to be drawn, updated, or otherwise 
 * be intereacted with as a group */
class DrawGroup {
	public:
		// TODO: Write with functionality to not use MegaBase for the renderer and offset
		DrawGroup() {}
		virtual ~DrawGroup() {}
		virtual int size() = 0;
		virtual void clearGroup() = 0;
		virtual void drawGroup() = 0;
};
#endif
