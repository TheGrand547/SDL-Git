#pragma once
#ifndef DRAW_GROUP_H
#define DRAW_GROUP_H
#include<SDL2/SDL.h>
#include "../BoundedPoint.h"
class DrawGroup {
	/*
	protected:
		static SDL_Renderer* renderer;*/
	public:
		static SDL_Renderer* renderer;
		DrawGroup() {}
		virtual ~DrawGroup() {}
		virtual void drawGroup(BoundedPoint& screenPosition) = 0;
		static void SET_RENDERER(SDL_Renderer* renderer) {
			DrawGroup::renderer = renderer;
		}
};
#endif
