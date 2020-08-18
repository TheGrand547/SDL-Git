#include "Surface.h"

// Stupid macro
#define CHECK if (this->locked) LOG("Attempting to modify a locked surface!"); \
				if (!this->surface) return;

Surface::Surface() : changed(false), locked(false), surface(NULL) {}

Surface::Surface(const Surface& surface) : changed(false), locked(false) {
	*this = surface;
}

Surface::Surface(Surface&& surface) : changed(false), locked(false) {
	*this = std::forward<Surface>(surface);
}

Surface::Surface(SDL_Surface*& surface) : changed(false), locked(false) {
	*this = surface;
}

Surface::Surface(SDL_Surface*&& surface) : changed(false), locked(false) {
	*this = std::forward<SDL_Surface*>(surface);
}

Surface::~Surface() {
	this->free();
}

SDL_Surface* Surface::createSurface(const int& width, const int& height) const {
	// TODO: 8 should be constant'd, once we figure out what it does
	return SDL_CreateRGBSurface(SURFACE_FLAGS, width, height, PIXEL_DEPTH, RMASK, GMASK, BMASK, AMASK);
}

Surface& Surface::operator=(SDL_Surface*&& surface) {
	// rvalue, clear
	this->free();
	this->locked = false;
	this->changed = true;
	this->surface = surface;
	surface = NULL;
	return *this;
}

Surface& Surface::operator=(Surface&& surface) {
	// rvalue, clear
	this->free();
	this->locked = false;
	this->changed = true;
	this->surface = surface.surface;
	surface.surface = NULL;
	return *this;
}


Surface& Surface::operator=(SDL_Surface*& surface) {
	// lvalue, copy
	this->free();
	this->locked = false;
	this->changed = true;
	this->surface = this->createSurface(surface->w, surface->h);
	if (this->surface) SDL_BlitSurface(surface, NULL, this->surface, NULL);
	else LOG("Created Invalid Blank Surface. ");
	return *this;
}

Surface& Surface::operator=(const Surface& surface) {
	// lvalue, copy
	if (this != &surface) {
		this->free();
		this->locked = false;
		this->changed = true;
		this->surface = this->createSurface(surface.surface->w, surface.surface->h);
		if (this->surface) surface.blitTo(*this);
		else LOG("Created Invalid Blank Surface. ");
	}
	return *this;
}

Color Surface::getColorKey() const {
	if (!this->surface) return Color();
	Color color;
	Uint32 key;
	SDL_GetColorKey(this->surface, &key);
	SDL_GetRGBA(key, this->surface->format, &color.r, &color.g, &color.b, &color.a);
	return color;
}

int Surface::blitTo(Surface& surface, const Rect& srcRect, const Rect& dstRect) const {
	SDL_Rect src = srcRect.getSDLRect(), dst = dstRect.getSDLRect();
	// Accelerate blitting if possible
	if (!SDL_MUSTLOCK(this->surface)) SDL_SetSurfaceRLE(this->surface, true);
	if (!SDL_MUSTLOCK(surface.surface)) SDL_SetSurfaceRLE(surface.surface, true);
	return SDL_BlitSurface(this->surface, (srcRect.isReal()) ? &src : NULL, surface.surface, (dstRect.isReal()) ? &dst : NULL);
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

int Surface::setColorMod(const Uint8& r, const Uint8& g, const Uint8& b) const {
	return SDL_SetSurfaceColorMod(this->surface, r, g, b);
}

int Surface::setColorMod(const Color& color) const {
	return SDL_SetSurfaceColorMod(this->surface, color.r, color.g, color.b);
}

void Surface::free() {
	if (this->surface) {
		SDL_FreeSurface(this->surface);
		this->surface = NULL;
		this->changed = true;
		this->locked = false;
	}
	this->internal.free();
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
	if (!this->surface && !this->locked) {
		LOG("Attempting to draw a NULL surface!");
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
	CHECK;
	if (std::abs(width) < ROUNDING || std::abs(height) < ROUNDING) return;
	SDL_Surface* old = this->surface;
	this->surface = rotozoomSurfaceXY(this->surface, 0, std::abs(width) / this->width(), std::abs(height) / this->height(), smooth);
	if (this->surface) {
		SDL_FreeSurface(old);
		this->changed = true;
	}
	else this->surface = old;
}

void Surface::setColorKey(const Uint32& _color) {
	// Assume it is already in 0xRRGGBBAA
	Color color(_color);
	this->setColorKey(Color(SDL_MapRGBA(this->surface->format, color.r, color.g, color.b, color.a)));
}

void Surface::setColorKey(const SDL_Color& color) {
	// Should be in 0xRRGGBBAA format already so just map it
	SDL_SetColorKey(this->surface, true, SDL_MapRGBA(this->surface->format, color.r, color.g, color.b, color.a));
}

void Surface::finalize(SDL_Renderer* renderer) {
	if (this->surface) {
		this->internal = SDL_CreateTextureFromSurface(renderer, this->surface);
		SDL_FreeSurface(this->surface);
		this->surface = NULL;
		this->locked = true;
		this->changed = false;
	} else LOG("Attempting to finalize a NULL surface.");
	
}

void Surface::fillRects(std::vector<Rect>& vec, const Uint32& color) {
	// Assume RGBA
	Color _color(color);
	Uint32 fill = SDL_MapRGBA(this->surface->format, _color.r, _color.g, _color.b, _color.a);
	SDL_Rect* rects = new SDL_Rect[vec.size()];
	for (uint i = 0; i < vec.size(); i++) rects[i] = vec[i].getSDLRect();
	SDL_FillRects(this->surface, rects, vec.size(), fill);
	delete[] rects;

}

// ------------------------------------------------
// ------------ Non Essential Extras --------------
// ------------------------------------------------

void Surface::bilateralFilter(double valI, double valS, const int kernelSize, int xStart, int yStart, int width, int height) {
	CHECK;
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

void Surface::dither() {
	CHECK;
	PixelMod mod(this->surface);
	this->changed = true;
	Uint8 matrix[2][2] = {{0x40, 0x80}, 
						  {0xC0, 0x00}};
	Uint8 value;
	for (int i = 0; i < mod.count(); i++) {
		Pixel pixel = mod.getPixel(i);
		value = matrix[(i / mod.width()) % 2][(i / mod.height()) % 2];
		pixel.red() = (pixel.red() < value) ? 0x00 : 0xFF;
		pixel.green() = (pixel.green() < value) ? 0x00 : 0xFF;
		pixel.blue() = (pixel.blue() < value) ? 0x00 : 0xFF;
	}
	/* TODO: Floyd–Steinberg dithering
	for (int x = 1; x < mod.width(); x++) {
		for (int y = 0; y < mod.height(); y++) {
			Pixel pixel = mod.getPixel(x, y);
			Pixel old = 
		}
	}*/
}

void Surface::floatyEdges() {
	CHECK;
	this->setBlend(BLEND);
	PixelMod mod(this->surface);
	this->changed = true;
	int aAvg, count;
	for (int x = 0; x < mod.width(); x++) {
		for (int y = 0; y < mod.height(); y++) {
			Pixel pixel = mod.getPixel(x, y);
			if (pixel.alpha() < 0x4F) continue;
			aAvg = 0;
			count = 0;
			for (int subX = -1; subX <= 1; subX++) {
				for (int subY = -1; subY <= 1; subY++) {
					Pixel temp = mod.getPixel(x + subX, y + subY);
					if (temp.alpha() == 0x00) count++;
					aAvg += temp.alpha();
					count++;
				}
			}
			aAvg /= count;
			pixel.setAlpha(aAvg);
		}
	}
}

void Surface::limitPalette() {
	CHECK;
	PixelMod mod(this->surface);
	this->changed = true;
	for (int i = 0; i < mod.count(); i++) {
		Pixel pixel = mod.getPixel(i);
		pixel.red() = (pixel.red() / 16) * 16;
		pixel.green() = (pixel.green() / 16) * 16;
		pixel.blue() = (pixel.blue() / 16) * 16;
	}
}

void Surface::testFilter() {
	CHECK;
	PixelMod mod(this->surface);
	this->changed = true;
	for (int x = 0; x < mod.width(); x++) {
		for (int y = 0; y < mod.height(); y++) {
			Pixel main = mod.getPixel(x, y);
			Pixel left = mod.getPixel(x - 1, y);
			Pixel right = mod.getPixel(x + 1, y);
			main.red() = (main.red() + left.red() + right.red()) / 3;
			main.green() = (main.green() + left.green() + right.green()) / 3;
			main.blue() = (main.blue() + left.blue() + right.blue()) / 3;
		}
	}
}
