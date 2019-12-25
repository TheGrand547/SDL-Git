#include "PixelMod.h"

PixelMod::PixelMod(SDL_Texture* texture) : texture(texture) {
	void* rawPixels;
	uint32 format;
	this->unlocked = false;
	if (SDL_LockTexture(texture, NULL, &rawPixels, &this->pitch) != 0) {
		this->unlocked = true;
		return;
	}
	SDL_QueryTexture(this->texture, &format, NULL, &this->width, &this->height);
	this->format = SDL_AllocFormat(format);
	this->pixels = (uint32*)rawPixels;
	this->pixelCount = (this->pitch / 4) * this->height;
}

PixelMod::~PixelMod() {
	if (!this->unlocked) {
		SDL_UnlockTexture(this->texture);
		SDL_FreeFormat(this->format);
	}
}

bool PixelMod::notLocked() {
	return this->unlocked;
}

uint32& PixelMod::at(int x, int y) {
	if (x < 0 || x > (this->width - 1) || y < 0 || y > (this->height - 1)) {
		// If the requested position is outside of the array return a blank pixel with no data in it
		this->UGLY = 0x00000000; // Reset the UGLY value
		return this->UGLY;
	}
	return this->pixels[x + (y * this->height)];
}

uint32 PixelMod::mapRGBA(const uint8 r, const uint8 g, const uint8 b, const uint8 a) const {
	return SDL_MapRGBA(this->format, r, g, b, a);
}

Pixel PixelMod::getPixel(int index) {
	Pixel pixel(this->pixels[index], this->format);
	return pixel;
}

Pixel PixelMod::getPixel(int x, int y) {
	Pixel pixel(this->at(x, y), this->format);
	return pixel;
}

uint32& PixelMod::operator[](const int index) {
	return this->pixels[index];
}
