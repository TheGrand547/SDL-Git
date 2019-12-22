#ifndef PIXEL_CLASS_H
#define PIXEL_CLASS_H
#include<SDL2/SDL.h>
#include "Point.h"

typedef uint8_t uint8;
typedef uint32_t uint32;
class Pixel {
	private:
		Point position;
		SDL_PixelFormat* format;
		uint8 red, green, blue, alpha;
	public:
		Pixel(Point position, uint32 data, SDL_PixelFormat* format);
		Pixel(float x, float y, uint32 data, SDL_PixelFormat* format);
		~Pixel();
	
};
#endif
