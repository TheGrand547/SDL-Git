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

Pixel::Pixel(const Pixel& that) {
	this->position = that.position;
	this->format = that.format;
	this->original = that.original; // Directly copy the pointer so they keep the same target
	SDL_GetRGBA(*this->original, this->format, &this->r, &this->g, &this->b, &this->a);
}

Pixel::~Pixel() {
	// When the object goes out of scope, apply changes
	if (this->original != NULL) {
		*this->original = SDL_MapRGBA(this->format, this->r, this->g, this->b, this->a); 
	}
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

void Pixel::setRed(const uint8 red) {
	this->r = red;
}

void Pixel::setBlue(const uint8 blue) {
	this->b = blue;
}

void Pixel::setGreen(const uint8 green) {
	this->g = green;
}

void Pixel::setAlpha(const uint8 alpha) {
	this->a = alpha;
}

void Pixel::update() {
	*this->original = SDL_MapRGBA(this->format, this->r, this->g, this->b, this->a); 
}

void Pixel::empty() {
	this->update();
	this-> original = NULL;
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

