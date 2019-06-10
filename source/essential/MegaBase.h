#pragma once
#ifndef MEGA_BASE_H
#define MEGA_BASE_H
#include<SDL2/SDL.h>
#include "../BoundedPoint.h"
class MegaBase {
	public:
		static SDL_Renderer* renderer;
		static BoundedPoint* offset;
		static void setRenderer(SDL_Renderer* renderer) {
			MegaBase::renderer = renderer;
		}
		static void setOffset(BoundedPoint* offset) {
			MegaBase::offset = offset;
		}
};
#endif
