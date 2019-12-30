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
		uint32* original;
		uint8 r, g, b, a;
	public:
		Pixel(uint32& data, SDL_PixelFormat* format);
		Pixel(Point position, uint32& data, SDL_PixelFormat* format);
		Pixel(float x, float y, uint32& data, SDL_PixelFormat* format);
		Pixel(const Pixel& that);
		~Pixel();
		void empty();
		void setRed(const uint8 red);
		void setBlue(const uint8 blue);
		void setGreen(const uint8 green);
		void setAlpha(const uint8 alpha);
		void update();
		uint8& red();
		uint8& green();
		uint8& blue();
		uint8& alpha();
		uint32& source() const;
		Pixel& operator=(const uint32& other);
};
bool operator==(const Pixel& lhs, const uint32& rhs);
bool operator==(const uint32& lhs, const Pixel& rhs);
bool operator!=(const Pixel& lhs, const uint32& rhs);
bool operator!=(const uint32& lhs, const Pixel& rhs);
#endif
