#ifndef PIXEL_CLASS_H
#define PIXEL_CLASS_H
#include<SDL2/SDL.h>
#include "Point.h"

typedef uint8_t Uint8;
typedef uint32_t Uint32;

class Pixel {
	protected:
		Point position;
		SDL_PixelFormat* format;
		Uint32* original;
		Uint8 r, g, b, a;
	public:
		Pixel();
		Pixel(Uint32& data, SDL_PixelFormat* format);
		Pixel(Point position, Uint32& data, SDL_PixelFormat* format);
		Pixel(double x, double y, Uint32& data, SDL_PixelFormat* format);
		Pixel(const Pixel& that);
		~Pixel();
		void empty();
		void setRed(const Uint8& red);
		void setBlue(const Uint8& blue);
		void setGreen(const Uint8& green);
		void setAlpha(const Uint8& alpha);
		void update();
		Uint8& red();
		Uint8& green();
		Uint8& blue();
		Uint8& alpha();
		Uint32& source() const;
		Pixel& operator=(const Uint32& other);
};
bool operator==(const Pixel& lhs, const Uint32& rhs);
bool operator==(const Uint32& lhs, const Pixel& rhs);
bool operator!=(const Pixel& lhs, const Uint32& rhs);
bool operator!=(const Uint32& lhs, const Pixel& rhs);
#endif
