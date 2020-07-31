#pragma once
#ifndef SURFACE_H
#define SURFACE_H
#include<SDL.h>
#include<SDL2_rotozoom.h>
#include "../essential/SDL_Headers.h"
#inlcude "../primitives/Rect.h"

class Surface {
	private:
		// Methods there is no reason anyone outside should need to call
		SDL_Surface* createSurface(const int& width, const int& height);
	protected:
		SDL_Surface* surface;
		
	public:
		// TODO: Rearrange
		Surface();
		~Surface();
		
		Surface& operator=(SDL_Surface*&& surface);
		Surface& operator=(Surface&& surface);
		Surface& operator=(SDL_Surface*&& surface);
		Surface& operator=(Surface&& surface);
		
		int blitTo(Surface& surface, const Rect& srcRect = Rect(), const Rect& dstRect = Rect());
		void free();
		int setAlpha(const Uint8& alpha);
		int setBlend(const SDL_BLENDMODE& blend);
		int setBlend(const BLEND_MODE& blend);
};
#endif
