#include "Texture.h"

int SDL_SetRenderTarget(SDL_Renderer* renderer, Texture& texture) {
	return SDL_SetRenderTarget(renderer, texture.getRawTexture());
}

Texture::Texture() : width(0), height(0), renderer(NULL), texture(NULL) {}

Texture::~Texture() {
	this->free();
}

Texture::Texture(Texture&& that) {
	// rvalue texture constructor will be cleared
	this->free();
	this->texture = that.texture;
	this->width = that.width;
	this->height = that.height;
	that.texture = NULL;
}

Texture::Texture(const Texture& that) {
	// lvalue texture should be copied
	this->free();
	this->width = that.width;
	this->height = that.height;
	if (that.renderer != NULL) {
		this->texture = this->getBlankRenderTarget(that.renderer);
		SDL_SetRenderTarget(that.renderer, this->texture);
		SDL_RenderCopy(that.renderer, that.texture, NULL, NULL);
		SDL_SetRenderTarget(that.renderer, NULL);
		this->normalizeTexture(that.renderer);
	}
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

Texture& Texture::operator=(Texture& that) {
	// lvalue texture should be copied
	this->free();
	this->width = that.width;
	this->height = that.height;
	if (that.renderer != NULL) {
		this->texture = this->getBlankRenderTarget(that.renderer);
		SDL_SetRenderTarget(that.renderer, this->texture);
		SDL_RenderCopy(that.renderer, that.texture, NULL, NULL);
		SDL_SetRenderTarget(that.renderer, NULL);
		this->normalizeTexture(that.renderer);
	}
	return *this;
}

Texture& Texture::operator=(SDL_Texture*& that) {
	this->texture = that;
	that = NULL;
	return *this;
}

Texture& Texture::operator=(SDL_Texture*&& that) {
	// rvalue doesn't need to be cleared
	this->texture = that;
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
	int access, width, height;
	SDL_QueryTexture(this->texture, NULL, &access, &width, &height);
	if (access == SDL_TEXTUREACCESS_STREAMING) {
		return;
	} else if (access == SDL_TEXTUREACCESS_STATIC) { // Don't know what to do with it :(
		//LOG("Texture was created with the Texture Access of Static -> Fix This");
		SDL_Texture* streamingTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, width, height);
		
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
		SDL_Texture* streamingTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, width, height); 
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

Texture Texture::scaleTextureBy(SDL_Renderer* renderer, Texture texture, double xFactor, double yFactor) {
	// TODO: Fill in
	texture.getWidth();
	SDL_SetRenderTarget(renderer, NULL);
	xFactor++;
	yFactor++;
	return Texture();
}

// ------------------------------------------------
// ------------ Non Essential Extras --------------
// ------------------------------------------------
void Texture::floatyEdges() {
	if (this->texture == NULL) return;
	this->setBlend(SDL_BLENDMODE_BLEND);
	PixelMod mod(this->texture);
	if (mod.notLocked()) return;
	// TODO: Tidy this up at some point
	int aAvg, count;
	for (int x = 0; x < mod.width(); x++) {
		for (int y = 0; y < mod.height(); y++) {
			Pixel pixel = mod.getPixel(x, y);
			if (pixel.alpha() < 0x4F) {
				continue;
			}
			aAvg = 0;
			count = 0;
			for (int subX = -1; subX <= 1; subX++) {
				for (int subY = -1; subY <= 1; subY++) {
					Pixel temp = mod.getPixel(x + subX, y + subY);
					if (temp.alpha() == 0x00) {
						count++;
					}
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
void Texture::bilateralFilter(float valI, float valS, const int kernelSize,  const int xStart, const int yStart, int width, int height) {
	if (this->texture == NULL) return;
	PixelMod mod(this->texture, true);
	if (mod.notLocked()) return;
	{
		Pixel pixels[mod.width()][mod.height()]; // Using a static array is not only more elegant, it's also more performant
		for (int y = 0; y < mod.width(); y++) {
			for (int x = 0; x < mod.height(); x++) {
				pixels[x][y] = mod.getPixel(x, y);
			}
		}
		int half = kernelSize / 2;
		if (width == 0) {
			width = mod.width() - 2 - xStart;
		}
		if (height == 0) {
			height = mod.height() - 2 - yStart;
		}
		for (int x = xStart; x - xStart < width; x++) {
			for (int y = yStart; y - yStart < height; y++) {
				// For each pixel apply the filter
				float totalR(0), totalG(0), totalB(0);
				float weightR(0), weightG(0), weightB(0);
				for (int i = 0; i < kernelSize; i++) {
					for (int j = 0; j < kernelSize; j++) {
						int otherX = x - (half - i);
						int otherY = y - (half - j);
						float gaussIR = gaussian(pixels[otherX][otherY].red() - pixels[x][y].red(), valI);
						float gaussS = gaussian(Point(x, y).distanceToPoint(Point(otherX, otherY)), valS);
						double deltaR = gaussIR * gaussS;
						totalR += pixels[otherX][otherY].red() * deltaR;
						weightR += deltaR;
						
						float gaussIG = gaussian(pixels[otherX][otherY].green() - pixels[x][y].green(), valI);
						double deltaG = gaussIG * gaussS;
						totalG += pixels[otherX][otherY].green() * deltaG;
						weightG += deltaG;
						
						float gaussIB = gaussian(pixels[otherX][otherY].blue() - pixels[x][y].blue(), valI);
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
	}
}
