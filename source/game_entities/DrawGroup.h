#pragma once
#ifndef DRAW_GROUP_H
#define DRAW_GROUP_H
#include<SDL2/SDL.h>
#include "../BoundedPoint.h"
class DrawGroup {
	public:
		DrawGroup() {}
		virtual ~DrawGroup() {}
		virtual void drawGroup(SDL_Renderer* renderer, BoundedPoint& screenPosition) = 0;
};
#endif
