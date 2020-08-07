#include "Surface.h"

Surface::Surface() : changed(false), surface(NULL) {}

Surface::Surface(const Surface& surface) : changed(false) {
	*this = surface;
}

Surface::Surface(Surface&& surface) : changed(false) {
	*this = std::forward<Surface>(surface);
}

Surface::Surface(SDL_Surface*& surface) : changed(false){
	*this = surface;
}

Surface::Surface(SDL_Surface*&& surface) : changed(false){
	*this = std::forward<SDL_Surface*>(surface);
}

Surface::~Surface() {
	this->free();
}

SDL_Surface* Surface::createSurface(const int& width, const int& height) const {
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
		this->internal.free();
		this->surface = NULL;
		this->changed = true;
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

int Surface::height() const {
	if (this->surface) return this->surface->h;
	return -1;
}

int Surface::width() const {
	if (this->surface) return this->surface->w;
	return -1;
}

void Surface::draw(SDL_Renderer* renderer, Point position) {
	if (!this->surface) {
		LOG("Attempting to draw a null surface!");
		return;
	}
	if (this->changed) {
		this->internal = SDL_CreateTextureFromSurface(renderer, this->surface);
		this->changed = false;
	}
	this->internal.draw(renderer, position); 
}

void Surface::load(const std::string& path) {
	this->free();
	this->surface = IMG_Load(path.c_str());
	if (!this->surface) LOG("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
}

void Surface::scale(const double& width, const double& height, bool smooth) {
	if (std::abs(width) < ROUNDING || std::abs(height) < ROUNDING) return;
	SDL_Surface* old = this->surface;
	this->surface = rotozoomSurfaceXY(this->surface, 0, std::abs(width) / this->width(), std::abs(height) / this->height(), smooth);
	if (this->surface) {
		SDL_FreeSurface(old);
		this->changed = true;
	}
	else this->surface = old;
}


void Surface::bilateralFilter(double valI, double valS, const int kernelSize, int xStart, int yStart, int width, int height) {
	if (kernelSize % 2 == 0) {
		LOG("KernalSize MUST be odd.");
		return;
	}
	if (this->surface == NULL) return;
	this->changed = true;
	PixelMod mod(this->surface, true);
	
	#ifndef NDEBUG
	Uint32 start = SDL_GetTicks();
	#endif
	
	int half = kernelSize / 2;
	if (width == 0) width = mod.width();
	if (height == 0) height = mod.height();
	if (xStart == -1) xStart = kernelSize / 2;
	if (yStart == -1) yStart = kernelSize / 2;
	for (int x = xStart; x - xStart < width; x++) {
		for (int y = yStart; y - yStart < height; y++) {
			// For each pixel apply the filter
			double totalR(0), totalG(0), totalB(0);
			double weightR(0), weightG(0), weightB(0);
			SDL_Color current = mod.getPixel(x, y).getOriginalChannels();
			for (int i = 0; i < kernelSize; i++) {
				for (int j = 0; j < kernelSize; j++) {
					int otherX = x - (half - i);
					int otherY = y - (half - j);
					SDL_Color other = mod.getPixel(otherX, otherY).getOriginalChannels();
					double gaussIR = gaussian(other.r - current.r, valI);
					double gaussS = gaussian(Point(x, y).distanceToPoint(Point(otherX, otherY)), valS);
					double deltaR = gaussIR * gaussS;
					totalR += other.r * deltaR;
					weightR += deltaR;
					
					double gaussIG = gaussian(other.g - current.g, valI);
					double deltaG = gaussIG * gaussS;
					totalG += other.g * deltaG;
					weightG += deltaG;
					
					double gaussIB = gaussian(other.b - current.b, valI);
					double deltaB = gaussIB * gaussS;
					totalB += other.b * deltaB;
					weightB += deltaB;
				}
			}
			mod.getPixel(x, y).red() = totalR / weightR;
			mod.getPixel(x, y).green() = totalG / weightG;
			mod.getPixel(x, y).blue() = totalB / weightB;
		}
	}
	
	#ifndef NDEBUG
	LOG("Filter Time: %i", (int) SDL_GetTicks() - start);
	#endif
}
