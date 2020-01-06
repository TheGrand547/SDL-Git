#include "PixelMod.h"

PixelMod::PixelMod(SDL_Texture* texture, bool wrapEdges) : texture(texture) {
	this->edges = wrapEdges;
	void* rawPixels;
	uint32 format;
	this->unlocked = false;
	if (SDL_LockTexture(texture, NULL, &rawPixels, &this->texturePitch) != 0) {
		this->unlocked = true;
		// TODO: log error locking texture
		return;
	}
	SDL_QueryTexture(this->texture, &format, NULL, &this->textureWidth, &this->textureHeight);
	this->format = SDL_AllocFormat(format);
	this->pixels = (uint32*)rawPixels;
	this->pixelCount = (this->texturePitch / 4) * this->textureHeight;
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
	if (x < 0 || x > (this->width() - 1) || y < 0 || y > (this->height() - 1)) {
		// If the requested position is outside of the array return a blank pixel with no data in it
		if (this->edges) {
			if (x < 0) {
				x += this->width();
			}
			if (y < 0) {
				y += this->height();
			}
			if (x > this->width() - 1) {
				x -= this->width();
			}
			if (y > this->height() - 1) {
				y -= this->height();
			}
			return this->at(x, y);
		}
		this->UGLY = 0x00000000; // Reset the UGLY value
		return this->UGLY;
	}
	return this->pixels[x + (y * this->height())];
}

int PixelMod::count() const {
	return this->pixelCount;
}

int PixelMod::height() const {
	return this->textureHeight;
}

int PixelMod::pitch() const {
	return this->texturePitch;
}

int PixelMod::width() const {
	return this->textureWidth;
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
