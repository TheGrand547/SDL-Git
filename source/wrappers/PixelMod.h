#pragma once
#ifndef PIXEL_MOD_H
#define PIXEL_MOD_H
#include<SDL2/SDL.h>
#include "../primitives/Pixel.h"

typedef uint8 uint8_t;
typedef uint32 uint32_t;

class PixelMod {
	protected:
		SDL_Texture* texture;
		uint32 UGLY = 0x00000000;
		bool unlocked;
	public:
		int pitch, width, height, pixelCount;
		SDL_PixelFormat* format;
		uint32* pixels;
		
		PixelMod(SDL_Texture* texture);
		~PixelMod();
		bool notLocked();
		uint32& at(int x, int y);
		uint32& operator[](const int index);
		uint32 mapRGBA(const uint8 r, const uint8 g, const uint8 b, const uint8 a = 0xFF) const;
		Pixel getPixel(int index);
		Pixel getPixel(int x, int y);
};
#endif
