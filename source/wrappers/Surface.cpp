#include "Surface.h"

Surface::Surface() : surface(NULL) {}

Surface::Surface(const Surface& surface) {
	*this = surface;
}

Surface::Surface(Surface&& surface) {
	*this = std::forward<Surface>(surface);
}

Surface::Surface(SDL_Surface*& surface) {
	*this = surface;
}

Surface::Surface(SDL_Surface*&& surface) {
	*this = std::forward<SDL_Surface*>(surface);
}

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
	this->surface = surface.surface;
	surface.surface = NULL;
	return *this;
}


Surface& Surface::operator=(SDL_Surface*& surface) {
	// lvalue, copy
	this->free();
	this->surface = this->createSurface(surface->w, surface->h);
	if (this->surface) SDL_BlitSurface(surface, NULL, this->surface, NULL);
	else LOG("Created Invalid Blank Surface. ");
	return *this;
}

Surface& Surface::operator=(const Surface& surface) {
	// lvalue, copy
	if (this != &surface) {
		this->free();
		this->surface = this->createSurface(surface.surface->w, surface.surface->h);
		if (this->surface) surface.blitTo(*this);
		else LOG("Created Invalid Blank Surface. ");
	}
	return *this;
}


int Surface::blitTo(Surface& surface, const Rect& srcRect, const Rect& dstRect) const {
	SDL_Rect src = srcRect.getSDLRect(), dst = dstRect.getSDLRect();
	return SDL_BlitSurface(this->surface, (srcRect.isReal()) ? &src : NULL, surface.surface, (dstRect.isReal()) ? &dst : NULL);
}

void Surface::free() {
	if (this->surface) {
		SDL_FreeSurface(this->surface);
		this->surface = NULL;
	}
}

int Surface::setAlpha(const Uint8& alpha) {
	return SDL_SetSurfaceAlphaMod(this->surface, alpha);
}

int Surface::setBlend(const SDL_BlendMode& blend) {
	return SDL_SetSurfaceBlendMode(this->surface, blend);
}

int Surface::setBlend(const BLEND_MODE& blend) {
	return SDL_SetSurfaceBlendMode(this->surface, (SDL_BlendMode) blend);
}
