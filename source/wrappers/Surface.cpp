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


void Surface::bilateralFilter(double valI, double valS, const int kernelSize,  const int xStart, const int yStart, int width, int height) {
	if (this->surface == NULL) return;
	this->changed = true;
	PixelMod mod(this->surface, true);
	Uint32 start = SDL_GetTicks();
	{
		Pixel** pixels = new Pixel*[mod.width()];
		for (int i = 0; i < mod.width(); i++) pixels[i] = new Pixel[mod.height()];
		for (int y = 0; y < mod.width(); y++) {
			for (int x = 0; x < mod.height(); x++) {
				pixels[x][y] = mod.getPixel(x, y);
			}
		}
		int half = kernelSize / 2;
		if (width == 0) width = mod.width() - 2 - xStart;
		if (height == 0) height = mod.height() - 2 - yStart;
		for (int x = xStart; x - xStart < width; x++) {
			for (int y = yStart; y - yStart < height; y++) {
				// For each pixel apply the filter
				double totalR(0), totalG(0), totalB(0);
				double weightR(0), weightG(0), weightB(0);
				for (int i = 0; i < kernelSize; i++) {
					for (int j = 0; j < kernelSize; j++) {
						int otherX = x - (half - i);
						int otherY = y - (half - j);
						double gaussIR = gaussian(pixels[otherX][otherY].red() - pixels[x][y].red(), valI);
						double gaussS = gaussian(Point(x, y).distanceToPoint(Point(otherX, otherY)), valS);
						double deltaR = gaussIR * gaussS;
						totalR += pixels[otherX][otherY].red() * deltaR;
						weightR += deltaR;
						
						double gaussIG = gaussian(pixels[otherX][otherY].green() - pixels[x][y].green(), valI);
						double deltaG = gaussIG * gaussS;
						totalG += pixels[otherX][otherY].green() * deltaG;
						weightG += deltaG;
						
						double gaussIB = gaussian(pixels[otherX][otherY].blue() - pixels[x][y].blue(), valI);
						double deltaB = gaussIB * gaussS;
						totalB += pixels[otherX][otherY].blue() * deltaB;
						weightB += deltaB;
					}
				}
				pixels[x][y].red() = totalR / weightR;
				pixels[x][y].green() = totalG / weightG;
				pixels[x][y].blue() = totalB / weightB;
			}
		}
		for (int i = 0; i < mod.width(); i++) delete[] pixels[i];
		delete[] pixels;
	}
	LOG("Filter Time: %i", (int) SDL_GetTicks() - start);
}
