#pragma once
#ifndef PIXEL_MOD_H
#define PIXEL_MOD_H
#include "../essential/log.h"
#include "../essential/SDL_Headers.h"
#include "../primitives/Pixel.h"
#include "Surface.h"
#include <SDL2/SDL.h>

typedef uint8_t Uint8;
typedef uint32_t Uint32;

class PixelMod {
	protected:
		bool edges, isSurface, locked;
		int _height, _pitch, _width, pixelCount;
		SDL_PixelFormat* format;

		SDL_Surface* surface;
		SDL_Texture* texture;

		Uint32 UGLY = 0x00000000;
		Uint32* pixels;
		void deallocate();
	public:	
		PixelMod(const Surface& surface, bool wrapEdges = true);
		PixelMod(SDL_Surface* texture, bool wrapEdges = true);
		PixelMod(SDL_Texture* texture, bool wrapEdges = true);
		~PixelMod();
		bool notLocked();
		int count() const;
		int height() const;
		int pitch() const;
		int width() const;
		Pixel getPixel(int index);
		Pixel getPixel(int x, int y);
		Uint32& at(int x, int y);
		Uint32& operator[](const int index);
		Uint32 mapRGBA(const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 a = 0xFF) const;
};
#endif
