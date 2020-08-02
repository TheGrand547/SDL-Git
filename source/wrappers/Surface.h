#pragma once
#ifndef SURFACE_H
#define SURFACE_H
#include<SDL.h>
#include<SDL2_rotozoom.h>
#include "../essential/SDL_Headers.h"
#include "../primitives/Rect.h"

class Surface {
	private:
		// Methods there is no reason anyone outside should need to call
		SDL_Surface* createSurface(const int& width, const int& height) const;
	protected:
		SDL_Surface* surface;
		
	public:
		// TODO: Rearrange
		Surface();
		Surface(const Surface& surface);
		Surface(Surface&& surface);
		Surface(SDL_Surface*& surface);
		Surface(SDL_Surface*&& surface);
		~Surface();
		
		Surface& operator=(SDL_Surface*&& surface);
		Surface& operator=(Surface&& surface);
		Surface& operator=(SDL_Surface*& surface);
		Surface& operator=(const Surface& surface);
		
		int blitTo(Surface& surface, const Rect& srcRect = Rect(), const Rect& dstRect = Rect()) const;
		void free();
		int setAlpha(const Uint8& alpha);
		int setBlend(const SDL_BlendMode& blend);
		int setBlend(const BLEND_MODE& blend);
};
#endif
