#include "Surface.h"

Surface::Surface() : surface(NULL) {}

Surface::~Surface() {
	this->free();
}

SDL_Surface* Surface::createSurface(const int& width, const int& height) {
	// TODO: 8 should be constant'd, once we figure out what it does
	return SDL_CreateRGBSurface(SURFACE_FLAGS, width, height, 8, RMASK, GMASK, BMASK, AMASK);
}

Surface& Surface::operator=(SDL_Surface*&& surface) {
	// rvalue, clear
	this->free();
	this->surface = surface;
	surface = NULL;
	return *this;
}

Surface& Surface::operator=(Surface&& surface) {
	// rvalue, clear
	this->free();
	this->surface = surface;
	surface.surface = NULL;
	return *this;
}


// TODO: Figure out how i fucked this up
Surface& Surface::operator=(SDL_Surface*& surface) {
	// rvalue, clear
	this->free();
	this->surface = surface;
	surface = NULL;
	return *this;
}

Surface& Surface::operator=(Surface& surface) {
	// rvalue, clear
	this->free();
	this->surface = surface.surface;
	surface.surface = NULL;
	return *this;
}


int Surface::blitTo(Surface& surface, const Rect& srcRect, const Rect& dstRect) {
	SDL_Rect src = srcRect.getSDLRect(), dst = dstRect.getSDLRect();
	if (srcRect.isReal()) {
		if (dstRect.isReal()) {
			return SDL_BlitSurface(this->surface, &src, surface.surface, &dst);
		} else {
			return SDL_BlitSurface(this->surface, &src, surface.surface, NULL);
		}
	} else {
		if (dstRect.isReal()) {
			return SDL_BlitSurface(this->surface, NULL, surface.surface, &dst);
		} else {
			return SDL_BlitSurface(this->surface, NULL, surface.surface, NULL);
		}
	}
}

void Surface::free() {
	if (this->surface) {
		SDL_DestroySurface(this->surface);
		this->surface = NULL;
	}
}

int Surface::setAlpha(const Uint8& alpha) {
	return SDL_SetSurfaceAlphaMod(this->surface, alpha);
}

int Surface::setBlend(const SDL_BLENDMODE& blend) {
	return SDL_SetSurfaceBlendMode(this->surface, blend);
}

int Surface::setBlend(const BLEND_MODE& blend) {
	return SDL_SetSurfaceBlendMode(this->surface, blend);
}
