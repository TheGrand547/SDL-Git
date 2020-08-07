#include "Pixel.h"

Pixel::Pixel() : format(NULL), original(NULL) {}

Pixel::Pixel(Uint32& data, SDL_PixelFormat* format) : format(format), original(&data) {
	SDL_GetRGBA(data, this->format, &this->r, &this->g, &this->b, &this->a);
}

Pixel::Pixel(Point position, Uint32& data, SDL_PixelFormat* format) : position(position), format(format), original(&data) {
	// Pointer to the original data for the purposes of changing the original
	SDL_GetRGBA(data, this->format, &this->r, &this->g, &this->b, &this->a);
}

Pixel::Pixel(double x, double y, Uint32& data, SDL_PixelFormat* format) {
	*this = Pixel(Point(x, y), data, format);
}

Pixel::Pixel(const Pixel& that) : position(that.position), format(that.format), original(that.original) {
	// Directly copy the pointer so they keep the same target
	SDL_GetRGBA(*this->original, this->format, &this->r, &this->g, &this->b, &this->a);
}

Pixel::~Pixel() {
	// When the object goes out of scope, apply changes
	if (this->original != NULL) {
		*this->original = SDL_MapRGBA(this->format, this->r, this->g, this->b, this->a); 
	}
}

Pixel& Pixel::operator=(const Uint32& other) {
	*this->original = other;
	SDL_GetRGBA(other, this->format, &this->r, &this->g, &this->b, &this->a);
	return *this;
}

SDL_Color Pixel::getOriginalChannels() const {
	SDL_Color color;
	SDL_GetRGBA(*this->original, this->format, &color.r, &color.g, &color.b, &color.a);
	return color;
}

Uint8& Pixel::red() {
	return this->r;
}

Uint8& Pixel::green() {
	return this->g;
}

Uint8& Pixel::blue() {
	return this->b;
}

Uint8& Pixel::alpha() {
	return this->a;
}

Uint32& Pixel::source() const {
	return *this->original;
}

void Pixel::setRed(const Uint8& red) {
	this->r = red;
}

void Pixel::setBlue(const Uint8& blue) {
	this->b = blue;
}

void Pixel::setGreen(const Uint8& green) {
	this->g = green;
}

void Pixel::setAlpha(const Uint8& alpha) {
	this->a = alpha;
}

void Pixel::update() {
	if (this->original != NULL) {
		*this->original = SDL_MapRGBA(this->format, this->r, this->g, this->b, this->a); 
	}
}

void Pixel::empty() {
	this->update();
	this->original = NULL;
}

bool operator==(const Pixel& lhs, const Uint32& rhs) {
	return lhs.source() == rhs;
}

bool operator==(const Uint32& lhs, const Pixel& rhs) {
	return rhs.source() == lhs;
}

bool operator!=(const Pixel& lhs, const Uint32& rhs) {
	return !(lhs == rhs);
}

bool operator!=(const Uint32& lhs, const Pixel& rhs) {
	return !(lhs == rhs);
}
