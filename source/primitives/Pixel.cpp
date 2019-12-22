#include "Pixel.h"

Pixel::Pixel(Point position, uint32 data, SDL_PixelFormat* format) {
	this->position = position;
}

Pixel::Pixel(float x, float y, uint32 data, SDL_PixelFormat* format) {
	*this = Pixel(Point(x, y), data, format);
}

Pixel::~Pixel() {}

