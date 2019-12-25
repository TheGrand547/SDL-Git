#include "Pixel.h"

Pixel::Pixel(uint32& data, SDL_PixelFormat* format) {
	this->original = &data;
	this->format = format;
	SDL_GetRGBA(data, this->format, &this->r, &this->g, &this->b, &this->a);
}

Pixel::Pixel(Point position, uint32& data, SDL_PixelFormat* format) {
	this->position = position;
	this->format = format;
	this->original = &data; // Pointer to the original data for the purposes of changing the original
	SDL_GetRGBA(data, this->format, &this->r, &this->g, &this->b, &this->a);
}

Pixel::Pixel(float x, float y, uint32& data, SDL_PixelFormat* format) {
	*this = Pixel(Point(x, y), data, format);
}

Pixel::~Pixel() {
	*this->original = SDL_MapRGBA(this->format, this->r, this->g, this->b, this->g);
}

uint8& Pixel::red() {
	return this->r;
}

uint8& Pixel::green() {
	return this->g;
}

uint8& Pixel::blue() {
	return this->b;
}

uint8& Pixel::alpha() {
	return this->a;
}

uint32& Pixel::source() const {
	return *this->original;
}

Pixel& Pixel::operator=(const uint32& other) {
	*this->original = other;
	SDL_GetRGBA(other, this->format, &this->r, &this->g, &this->b, &this->a);
	return *this;
}

bool operator==(const Pixel& lhs, const uint32& rhs) {
	return lhs.source() == rhs;
}

bool operator==(const uint32& lhs, const Pixel& rhs) {
	return rhs.source() == lhs;
}

bool operator!=(const Pixel& lhs, const uint32& rhs) {
	return !(lhs == rhs);
}

bool operator!=(const uint32& lhs, const Pixel& rhs) {
	return !(lhs == rhs);
}

