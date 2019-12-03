#pragma once
#ifndef PIXEL_MOD_H
#define PIXEL_MOD_H
#include<SDL2/SDL.h>
typedef Uint32 uint32_t;

class PixelMod {
	protected:
		SDL_Texture* texture;
		Uint32 UGLY = 0x00000000;
		bool unlocked;
	public:
		int pitch, width, height, pixelCount;
		SDL_PixelFormat* format;
		Uint32* pixels;
		
		PixelMod(SDL_Texture* texture);
		~PixelMod();
		bool notLocked();
		Uint32& at(int x, int y);
};
#endif
