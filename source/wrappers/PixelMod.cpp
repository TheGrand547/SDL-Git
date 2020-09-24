#include "PixelMod.h"

PixelMod::PixelMod(const Surface& surface, bool wrapEdges) : edges(wrapEdges), isSurface(true), surface(surface.surface) {
	if ((this->locked = SDL_MUSTLOCK(surface.surface)) && SDL_LockSurface(this->surface)) {
		LOG("Error Locking Surface: %s", SDL_GetError());
		this->locked = false;
		return;
	}
	this->_height = this->surface->h;
	this->_width = this->surface->w;
	this->_pitch = this->surface->pitch;
	this->format = this->surface->format;
	this->pixels = (Uint32*) this->surface->pixels;
	this->pixelCount = (this->_pitch / this->format->BytesPerPixel) * this->_height;
}

PixelMod::PixelMod(SDL_Surface* surface, bool wrapEdges) : edges(wrapEdges), isSurface(true), surface(surface) {
	if ((this->locked = SDL_MUSTLOCK(surface)) && SDL_LockSurface(this->surface)) {
		LOG("Error Locking Surface: %s", SDL_GetError());
		this->locked = false;
		return;
	}
	this->_height = this->surface->h;
	this->_width = this->surface->w;
	this->_pitch = this->surface->pitch;
	this->format = this->surface->format;
	this->pixels = (Uint32*) this->surface->pixels;
	this->pixelCount = (this->_pitch / this->format->BytesPerPixel) * this->_height;
}

PixelMod::PixelMod(SDL_Texture* texture, bool wrapEdges) : edges(wrapEdges), isSurface(false), locked(true), texture(texture) {
	void* rawPixels;
	Uint32 format;
	SDL_QueryTexture(this->texture, &format, NULL, &this->_width, &this->_height);
	this->format = SDL_AllocFormat(format);
	
	if (SDL_LockTexture(texture, NULL, &rawPixels, &this->_pitch) || this->format->BytesPerPixel < 4) {
		LOG("Error Locking Texture: %s", SDL_GetError());
		this->locked = false;
		SDL_FreeFormat(this->format);
		return;
	}
	this->pixels = (Uint32*) rawPixels;
	this->pixelCount = (this->_pitch / this->format->BytesPerPixel) * this->_height;
}

PixelMod::~PixelMod() {
	this->deallocate();
}

bool PixelMod::notLocked() {
	return !this->locked;
}

int PixelMod::count() const {
	return this->pixelCount;
}

int PixelMod::height() const {
	return this->_height;
}

int PixelMod::pitch() const {
	return this->_pitch;
}

int PixelMod::width() const {
	return this->_width;
}

Pixel PixelMod::getPixel(int index) {
	Pixel pixel(this->pixels[index], this->format);
	return pixel;
}

Pixel PixelMod::getPixel(int x, int y) {
	Pixel pixel(this->at(x, y), this->format);
	return pixel;
}

Uint32& PixelMod::operator[](const int index) {
	return this->pixels[index];
}

Uint32& PixelMod::at(int x, int y) {
	if (x < 0 || x > (this->width() - 1) || y < 0 || y > (this->height() - 1)) {
		// If the requested position is outside of the array return a blank pixel with no data in it
		if (this->edges) {
			if (x < 0) x += this->width();
			if (y < 0) y += this->height();
			if (x > this->width() - 1) x -= this->width();
			if (y > this->height() - 1) y -= this->height();
			return this->at(x, y);
		}
		this->UGLY = 0x00000000; // Reset the UGLY value
		return this->UGLY;
	}
	return this->pixels[x + (y * this->height())];
}

Uint32 PixelMod::mapRGBA(const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 a) const {
	return SDL_MapRGBA(this->format, r, g, b, a);
}

void PixelMod::deallocate() {
	if (this->locked) {
		if (this->isSurface) {
			SDL_UnlockSurface(this->surface);
			return;
		}
		if (this->format) SDL_FreeFormat(this->format);
		SDL_UnlockTexture(this->texture);
	}
}
