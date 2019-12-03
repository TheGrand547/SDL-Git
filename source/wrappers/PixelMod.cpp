#include "PixelMod.h"

PixelMod::PixelMod(SDL_Texture* texture) : texture(texture) {
	void* rawPixels;
	Uint32 format;
	this->unlocked = false;
	if (SDL_LockTexture(texture, NULL, &rawPixels, &this->pitch) != 0) {
		this->unlocked = true;
		return;
	}
	SDL_QueryTexture(this->texture, &format, NULL, &this->width, &this->height);
	this->format = SDL_AllocFormat(format);
	this->pixels = (Uint32*)rawPixels;
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

Uint32& PixelMod::at(int x, int y) {
	if (x < 0 || x > (this->width - 1) || y < 0 || y > (this->height - 1)) {
		// If the requested position is outside of the array return a blank pixel with no data in it
		this->UGLY = 0x00000000; // Reset the UGLY value
		return this->UGLY;
	}
	return this->pixels[x + (y * this->height)];
}
