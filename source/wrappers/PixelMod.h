#pragma once
#ifndef PIXEL_MOD_H
#define PIXEL_MOD_H
#include<SDL2/SDL.h>
#include "../essential/SDL_Headers.h"
#include "../primitives/Pixel.h"

typedef uint8_t Uint8;
typedef uint32_t Uint32;

class PixelMod {
	protected:
		SDL_Texture* texture;
		uint32 UGLY = 0x00000000;
		bool unlocked, edges;
		uint32* pixels;
		SDL_PixelFormat* format;
		int texturePitch, textureWidth, textureHeight, pixelCount;
	public:		
		PixelMod(SDL_Texture* texture, bool wrapEdges = false);
		~PixelMod();
		bool notLocked();
		int count() const;
		int height() const;
		int pitch() const;
		int width() const;
		Pixel getPixel(int index);
		Pixel getPixel(int x, int y);
		uint32& at(int x, int y);
		uint32& operator[](const int index);
		uint32 mapRGBA(const uint8 r, const uint8 g, const uint8 b, const uint8 a = 0xFF) const;
};
#endif
