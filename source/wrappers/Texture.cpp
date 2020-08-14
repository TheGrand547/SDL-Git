#include "Texture.h"

Texture::Texture() : width(0), height(0), renderer(NULL), texture(NULL) {}

Texture::~Texture() {
	this->free();
}

Texture::Texture(Texture&& that) {
	// rvalue texture constructor, rvalue will be cleared
	this->texture = that.texture;
	that.texture = NULL;
	SDL_QueryTexture(this->texture, NULL, NULL, &this->width, &this->height);
}

Texture::Texture(const Texture& that) {
	// lvalue texture should be copied
	if (this == &that) return;
	if (that.renderer != NULL) {
		this->texture = this->getBlankRenderTarget(that.renderer);
		SDL_SetRenderTarget(that.renderer, this->texture);
		SDL_RenderCopy(that.renderer, that.texture, NULL, NULL);
		SDL_SetRenderTarget(that.renderer, NULL);
		this->normalizeTexture(that.renderer);
		SDL_QueryTexture(this->texture, NULL, NULL, &this->width, &this->height);
	}
}

Texture::Texture(SDL_Texture*& texture) {
	// Figure out how to do do this
	/*
	if (this->renderer) {
		this->free();
		SDL_QueryTexture(texture, NULL, NULL, &this->width, &this->height);
		this->texture = this->getBlankRenderTarget(this->renderer);
		
	}*/
	std::cout << &texture << std::endl;
	LOG("This should never be called");
	SDL_QueryTexture(this->texture, NULL, NULL, &this->height, &this->height);
}

Texture::Texture(SDL_Texture*&& texture) : width(0), height(0){
	// rvalue
	this->texture = texture;
	texture = NULL;
	SDL_QueryTexture(this->texture, NULL, NULL, &this->width, &this->height);
}

Texture& Texture::operator=(Texture&& that) {
	// rvalue texture will be cleared
	this->free();
	this->texture = that.texture;
	this->width = that.width;
	this->height = that.height;
	that.texture = NULL;
	return *this;
}

Texture& Texture::operator=(const Texture& that) {
	// lvalue texture should be copied
	if (this != &that) {
		this->free();
		this->width = that.width;
		this->height = that.height;
		if (that.renderer != NULL) {
			this->texture = this->getBlankRenderTarget(that.renderer);
			SDL_SetRenderTarget(that.renderer, this->texture);
			SDL_RenderCopy(that.renderer, that.texture, NULL, NULL);
			SDL_SetRenderTarget(that.renderer, NULL);
		}
	}
	return *this;
}

Texture& Texture::operator=(SDL_Texture*& that) {
	// lvalue copy MAKE IT FUCKING COPY
	this->free();
	if (this->renderer) {
		SDL_QueryTexture(that, NULL, NULL, &this->width, &this->height);
		this->texture = this->getBlankRenderTarget(this->renderer);
		SDL_SetRenderTarget(this->renderer, this->texture);
		SDL_RenderCopy(this->renderer, that, NULL, NULL);
		SDL_SetRenderTarget(this->renderer, NULL);
	} else {
		LOG("This should never be called");
		this->texture = that;
		that = NULL;	
	}
	return *this;
}

Texture& Texture::operator=(SDL_Texture*&& that) {
	// rvalue clear
	this->free();
	this->texture = that;
	that = NULL;
	return *this;
}

SDL_Texture* Texture::getBlankRenderTarget(SDL_Renderer* renderer) {
	if (this->renderer == NULL) this->renderer = renderer;
	return SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, this->width, this->height);
}

int Texture::getHeight() const {
	return this->height;
}

int Texture::getWidth() const {
	return this->width;
}

void Texture::free() {
	if (this->texture != NULL) {
		SDL_DestroyTexture(texture);
		this->texture = NULL;	
	}
}

void Texture::setColorMod(Uint8 red, Uint8 green, Uint8 blue) {
	if (this->texture == NULL) return;
	SDL_SetTextureColorMod(this->texture, red, green, blue);
}

void Texture::setAlpha(Uint8 alpha) {
	if (this->texture == NULL) return;
	SDL_SetTextureAlphaMod(this->texture, alpha);
}

void Texture::setBlend(SDL_BlendMode mode) {
	if (this->texture == NULL) return;
	SDL_SetTextureBlendMode(this->texture, mode);
}

void Texture::setColorKey(Uint8 red, Uint8 green, Uint8 blue) { // Modified from lazyfoo.net
	if (this->texture == NULL) return;
	this->setBlend(SDL_BLENDMODE_BLEND);
	PixelMod mod(this->texture);
	if (mod.notLocked()) return;
	Uint32 colorKey = mod.mapRGBA(red, green, blue);
	Uint32 transparent = mod.mapRGBA(0xFF, 0xFF, 0xFF, 0x00);
	for (int i = 0; i < mod.count(); i++) {
		if (mod[i] == colorKey) {
			mod[i] = transparent;
		}
	}
}

void Texture::draw(SDL_Renderer* renderer, Point position, SDL_COPY_EX_ARGS) {
	if (this->renderer == NULL) this->renderer = renderer;
	if (this->texture == NULL) return;
	if (!this->width || !this->height) SDL_QueryTexture(this->texture, NULL, NULL, &this->width, &this->height);
	SDL_Rect renderQuad = {(int)position.x, (int)position.y, this->width, this->height};
	if (clip != NULL) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	SDL_RenderCopyEx(renderer, this->texture, clip, &renderQuad, angle, center, flip);
}

void Texture::drawCentered(SDL_Renderer* renderer, Point position, SDL_COPY_EX_ARGS) {
	if (!this->width || !this->height) SDL_QueryTexture(this->texture, NULL, NULL, &this->width, &this->height);
	this->draw(renderer, position - Point(this->width, this->height) / 2.0, clip, angle, center, flip);
}

bool Texture::isLoaded() {
	return this->texture != NULL;
}

bool Texture::notLoaded() {
	return this->texture == NULL;
}

void Texture::createBlank(SDL_Renderer* renderer, int w, int h, Uint32 color) {
	if (this->renderer == NULL) this->renderer = renderer;
	this->free();
	SDL_Surface* tempSurface = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);
	if (tempSurface != NULL) {
		this->width = w;
		this->height = h;
		SDL_FillRect(tempSurface, NULL, color);
		SDL_Texture* tempTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
		if (tempTexture == NULL) {
			LOG("Unable to create blank texture: Error %s", SDL_GetError());
		} else {
			this->texture = tempTexture;
		}
	}
	SDL_FreeSurface(tempSurface);
}

SDL_Texture*& Texture::getRawTexture() {
	return this->texture;
}

void Texture::loadFromFile(SDL_Renderer* renderer, std::string path, int xSize, int ySize) {
	if (this->renderer == NULL) this->renderer = renderer;
	this->free();
	SDL_Texture* newTexture = NULL;
	SDL_Surface* tempSurface = IMG_Load(path.c_str());	
	if (tempSurface == NULL) {
		LOG("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	} else {
		tempSurface = scaleToSize(tempSurface, xSize, ySize);
		newTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
		if (newTexture == NULL) {
			LOG("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
			return;
		}
	}
	SDL_FreeSurface(tempSurface);
	this->texture = newTexture;
	SDL_QueryTexture(this->texture, NULL, NULL, &this->width, &this->height);
	this->normalizeTexture(renderer);
}

void Texture::normalizeTexture(SDL_Renderer* renderer) {
	if (this->renderer == NULL) this->renderer = renderer;
	if (this->texture == NULL) return;
	// TODO: Make this not shit
	// Method to take a SDL_TEXTUREACCESS_TARGET and make it a SDL_TEXTUREACCESS_STREAMING for pixel modification
	int access;
	SDL_QueryTexture(this->texture, NULL, &access, &this->width, &this->height);
	if (access == SDL_TEXTUREACCESS_STREAMING) {
		return;
	} else if (access == SDL_TEXTUREACCESS_STATIC) { // Don't know what to do with it :(
		//LOG("Texture was created with the Texture Access of Static -> Fix This");
		SDL_Texture* streamingTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, this->width, this->height);
		
		SDL_SetRenderTarget(renderer, streamingTexture);
		this->setBlend(SDL_BLENDMODE_BLEND);
		SDL_RenderCopy(renderer, this->texture, NULL, NULL);
		SDL_SetRenderTarget(renderer, NULL);
		
		SDL_DestroyTexture(this->texture);
				
		this->texture = streamingTexture;
		this->normalizeTexture(renderer);
		return;
	} else {
		SDL_SetRenderTarget(renderer, this->texture);
		SDL_Texture* streamingTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, this->width, this->height); 
		void* streamingPixels;
		int streamingPitch;
		SDL_LockTexture(streamingTexture, NULL, &streamingPixels, &streamingPitch); 
		SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_RGBA32, streamingPixels, streamingPitch); 
		SDL_UnlockTexture(streamingTexture);
		SDL_SetRenderTarget(renderer, NULL);
		
		Uint8 alpha, colorR, colorG, colorB;
		SDL_BlendMode blend;
		SDL_GetTextureAlphaMod(this->texture, &alpha);
		SDL_GetTextureBlendMode(this->texture, &blend);
		SDL_GetTextureColorMod(this->texture, &colorR, &colorG, &colorB);
		
		SDL_SetTextureAlphaMod(streamingTexture, alpha);
		SDL_SetTextureBlendMode(streamingTexture, blend);
		SDL_SetTextureColorMod(this->texture, colorR, colorG, colorB);
		SDL_DestroyTexture(this->texture);
		this->texture = streamingTexture;
	}
}


// ------------------------------------------------
// --------------- Static Methods -----------------
// ------------------------------------------------

Texture Texture::load(SDL_Renderer* renderer, std::string path) {
	Texture temp;
	temp.loadFromFile(renderer, path);
	return temp;
}

// ------------------------------------------------
// ------------ Non Essential Extras --------------
// ------------------------------------------------
void Texture::floatyEdges() {
	if (this->texture == NULL) return;
	this->setBlend(SDL_BLENDMODE_BLEND);
	PixelMod mod(this->texture);
	if (mod.notLocked()) return;
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

void Texture::dither() {
	if (this->texture == NULL) return;
	PixelMod mod(this->texture);
	if (mod.notLocked()) return;
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
}

void Texture::testFilter() {
	if (this->texture == NULL) return;
	PixelMod mod(this->texture);
	if (mod.notLocked()) return;
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

// This sucks please ignore
void Texture::bilateralFilter(double valI, double valS, const int kernelSize, int xStart, int yStart, int width, int height) {
	if (this->texture == NULL) return;
	PixelMod mod(this->texture, true);
	if (mod.notLocked()) return;
	
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


// ------------------------------------------------
// -------------- Friend Functions ----------------
// ------------------------------------------------

int SDL_GetTextureAlphaMod(Texture& texture, Uint8* alpha) {
	return SDL_GetTextureAlphaMod(texture.texture, alpha);
}

int SDL_GetTextureAlphaMod(Texture& texture, Uint8& alpha) {
	return SDL_GetTextureAlphaMod(texture.texture, &alpha);
}

int SDL_GetTextureBlendMode(Texture& texture, SDL_BlendMode* blendMode) {
	return SDL_GetTextureBlendMode(texture.texture, blendMode);
}

int SDL_GetTextureBlendMode(Texture& texture, SDL_BlendMode& blendMode) {
	return SDL_GetTextureBlendMode(texture.texture, &blendMode);
}

int SDL_GetTextureColorMod(Texture& texture, Uint8* r, Uint8* g, Uint8* b) {
	return SDL_GetTextureColorMod(texture.texture, r, g, b);
}

int SDL_GetTextureColorMod(Texture& texture, Uint8& r, Uint8& g, Uint8& b) {
	return SDL_GetTextureColorMod(texture.texture, &r, &g, &b);
}

int SDL_LockTexture(Texture& texture, const SDL_Rect*& rect, void**& pixels, int*& pitch) {
	return SDL_LockTexture(texture.texture, rect, pixels, pitch);
}

int SDL_LockTexture(Texture& texture, const SDL_Rect& rect, void*& pixels, int& pitch) {
	return SDL_LockTexture(texture.texture, &rect, &pixels, &pitch);
}

int SDL_QueryTexture(Texture& texture, Uint32*& format, int* access, int* w, int* h) {
	return SDL_QueryTexture(texture.texture, format, access, w, h);
}

int SDL_QueryTexture(Texture& texture, Uint32& format, int& access, int& w, int& h) {
	return SDL_QueryTexture(texture.texture, &format, &access, &w, &h);
}

int SDL_RenderCopy(SDL_Renderer* renderer, Texture& texture, const SDL_Rect* src = NULL, const SDL_Rect* dst = NULL) {
	return SDL_RenderCopy(renderer, texture.texture, src, dst);
}

int SDL_RenderCopyEx(SDL_Renderer* renderer, Texture& texture, const SDL_Rect* src = NULL, const SDL_Rect* dst = NULL, const double& angle = 0, const SDL_Point* center = NULL, const SDL_RendererFlip& flip = SDL_FLIP_NONE) {
	return SDL_RenderCopyEx(renderer, texture.texture, src, dst, angle, center, flip);
}

int SDL_SetRenderTarget(SDL_Renderer* renderer, Texture& texture) {
	return SDL_SetRenderTarget(renderer, texture.texture);
}

int SDL_SetTextureAlphaMod(Texture& texture, const Uint8& alpha) {
	return SDL_SetTextureAlphaMod(texture.texture, alpha);
}

int SDL_SetTextureBlendMode(Texture& texture, SDL_BlendMode blendMode) {
	return SDL_SetTextureBlendMode(texture.texture, blendMode);
}

int SDL_SetTextureColorMod(Texture& texture, const Uint8& r, const Uint8& g, const Uint8& b) {
	return SDL_SetTextureColorMod(texture.texture, r, g, b);
}

void SDL_DestroyTexture(Texture& texture) {
	texture.free();
}

void SDL_UnlockTexture(Texture& texture) {
	SDL_UnlockTexture(texture.texture);
}
