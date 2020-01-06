#include "Texture.h"

Texture::Texture() {
	texture = NULL;
}

Texture::~Texture() {
	free();
}

Texture& Texture::operator=(const Texture& that) {
	this->xpos = that.xpos;
	this->ypos = that.ypos;
	this->texture = that.texture;
	return *this;
}

Texture::Texture(const Texture& that) {
	this->xpos = that.xpos;
	this->ypos = that.ypos;
	this->texture = that.texture;
}

void Texture::free() {
	if (texture != NULL) {
		SDL_DestroyTexture(texture);
		texture = NULL;	
	}
}

SDL_Surface* Texture::scaleToCoords(SDL_Surface* surf, float desiredWidth, float desiredHeight) {
	desiredWidth = (desiredWidth == 0) ? surf->w : desiredWidth;
	desiredHeight = (desiredHeight == 0) ? surf->w : desiredHeight;
	double xFactor = desiredWidth / surf->w;
	double yFactor = desiredHeight / surf->h;
	return rotozoomSurfaceXY(surf, 0, xFactor, yFactor, 1);
}

void Texture::setColorMod(uint8 red, uint8 green, uint8 blue) {
	SDL_SetTextureColorMod(this->texture, red, green, blue);
}

void Texture::setAlpha(uint8 alpha) {
	SDL_SetTextureAlphaMod(this->texture, alpha);
}

void Texture::setBlend(SDL_BlendMode mode) {
	SDL_SetTextureBlendMode(this->texture, mode);
}

void Texture::setColorKey(uint8 red, uint8 green, uint8 blue) { // Modified from lazyfoo.net
	this->setBlend(SDL_BLENDMODE_BLEND);
	PixelMod mod(this->texture);
	if (mod.notLocked()) {
		return;
	}
	uint32 colorKey = mod.mapRGBA(red, green, blue);
	uint32 transparent = mod.mapRGBA(0xFF, 0xFF, 0xFF, 0x00);
	for (int i = 0; i < mod.count(); i++) {
		if (mod[i] == colorKey) {
			mod[i] = transparent;
		}
	}
}

void Texture::floatyEdges() {
	this->setBlend(SDL_BLENDMODE_BLEND);
	PixelMod mod(this->texture);
	if (mod.notLocked()) {
		return;
	}
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
	PixelMod mod(this->texture);
	if (mod.notLocked()) {
		return;
	}
	uint8 matrix[2][2] = {{0x40, 0x80}, 
						  {0xC0, 0x00}};
	uint8 value;
	for (int i = 0; i < mod.count(); i++) {
		Pixel pixel = mod.getPixel(i);
		value = matrix[(i / mod.width()) % 2][(i / mod.height()) % 2];
		pixel.red() = (pixel.red() < value) ? 0x00 : 0xFF;
		pixel.green() = (pixel.green() < value) ? 0x00 : 0xFF;
		pixel.blue() = (pixel.blue() < value) ? 0x00 : 0xFF;
	}
}

void Texture::testFilter() {
	PixelMod mod(this->texture);
	if (mod.notLocked()) {
		return;
	}
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

void Texture::bilateralFilter(float valI, float valS, int kernelSize) {
	PixelMod mod(this->texture);
	if (mod.notLocked()) {
		return;
	}
	{
		/*
		std::vector<std::vector<Pixel>> pixels; // Test performance against below
		for (int x = 0; x < mod.width(); x++) {
			std::vector<Pixel> row;
			for (int y = 0; y < mod.height(); y++) {
				row.push_back(mod.getPixel(x, y));
			}
			pixels.push_back(row);
		}*/
		
		Pixel pixels[mod.width()][mod.height()];
		for (int y = 0; y < mod.width(); y++) {
			for (int x = 0; x < mod.height(); x++) {
				pixels[x][y] = mod.getPixel(x, y);
			}
		}
		std::cout << "D:" << std::endl;
		int half = kernelSize / 2;
		for (int x = half; x < mod.width() - half; x++) {
			for (int y = half; y < mod.height() - half; y++) {
				// For each pixel apply the filter
				float totalR(0), totalG(0), totalB(0);
				float weightR(0), weightG(0), weightB(0);
				for (int i = 0; i < kernelSize; i++) {
					for (int j = 0; j < kernelSize; i++) {
						int otherX = x - (half - i);
						int otherY = y - (half - j);
						float gaussIR = gaussian(pixels[otherX][otherY].red() - pixels[x][y].red(), valI);
						float gaussSR = gaussian(Point(x, y).distanceToPoint(Point(otherX, otherY)), valS);
						double deltaR = gaussIR * gaussSR;
						totalR += pixels[otherX][otherY].red() * deltaR;
						weightR += deltaR;
					}
				}
				pixels[x][y].red() = totalR / weightR;
			}
		}
	}
}

void Texture::draw(int x, int y, SDL_Renderer* renderer, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip) {
	int width, height, access;
	SDL_QueryTexture(this->texture, NULL, &access, &width, &height);
	// Including this on the off chance it's needed
	if (access != SDL_TEXTUREACCESS_STREAMING) {
		this->normalizeTexture(renderer);
	}
	SDL_Rect renderQuad = {x, y, width, height};
	if (clip != NULL) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	SDL_RenderCopyEx(renderer, this->texture, clip, &renderQuad, angle, center, flip);
}

void Texture::draw(SDL_Renderer* renderer, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip) {
	this->draw(this->xpos + 1, this->ypos + 1, renderer, clip, angle, center, flip);
}

void Texture::draw(SDL_Renderer* renderer, Point offset) {
	this->draw((this->xpos - offset.x()), (this->ypos - offset.y()), renderer);
}

void Texture::drawAt(SDL_Renderer* renderer, Point position, Point offset) {
	this->setPos(position);
	this->draw(renderer, offset);
}

bool Texture::isLoaded() {
	return this->texture != NULL;
}

bool Texture::notLoaded() {
	return this->texture == NULL;
}

void Texture::createBlank(SDL_Renderer* renderer, int w, int h, uint32_t color) {
	SDL_DestroyTexture(this->texture);
	SDL_Texture* toReturn = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, w, h);
	SDL_Texture* tempText = NULL;
	SDL_Surface* tempSurf = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);
	if (tempSurf != NULL) {
		SDL_FillRect(tempSurf, NULL, color);
		SDL_SetRenderTarget(renderer, toReturn);
		tempText = SDL_CreateTextureFromSurface(renderer, tempSurf);
		SDL_RenderCopy(renderer, tempText, NULL, NULL);
		SDL_SetRenderTarget(renderer, NULL);
		SDL_DestroyTexture(tempText);
		this->texture = toReturn;
	}
	SDL_FreeSurface(tempSurf);
}

SDL_Texture* Texture::getTexture() {
	return this->texture;
}

void Texture::setPos(int x, int y) {
	this->xpos = x;
	this->ypos = y;
}

void Texture::setPos(Point point) {
	this->xpos = point.x();
	this->ypos = point.y();
}

void Texture::loadFromFile(std::string path, SDL_Renderer* renderer, int xSize, int ySize) {
	SDL_Texture* newTexture = NULL;
	SDL_Texture* tempTexture = NULL;
	SDL_Surface* tempSurface = IMG_Load(path.c_str());	
	if (tempSurface == NULL) {
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	} else {
		tempSurface = scaleToCoords(tempSurface, xSize, ySize);
		if (this->texture == NULL) {
			tempTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, tempSurface->w, tempSurface->h);
		} else {
			int width, height;
			SDL_QueryTexture(this->texture, NULL, NULL, &width, &height);
			tempTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, width, height);
		}
		newTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
		if (newTexture == NULL) {
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		SDL_SetRenderTarget(renderer, tempTexture);
		SDL_Rect tempRect = {0, 0, tempSurface->w, tempSurface->h};
		SDL_RenderCopy(renderer, this->texture, NULL, NULL);
		SDL_RenderCopy(renderer, newTexture, NULL, &tempRect);
		SDL_SetRenderTarget(renderer, NULL);
	}
	SDL_FreeSurface(tempSurface);
	this->texture = tempTexture;
	this->normalizeTexture(renderer);
}

void Texture::normalizeTexture(SDL_Renderer* renderer) {
	// Method to take a SDL_TEXTUREACCESS_TARGET and make it a SDL_TEXTUREACCESS_STREAMING for pixel modification
	int access, width, height;
	SDL_QueryTexture(this->texture, NULL, &access, &width, &height);
	if (access == SDL_TEXTUREACCESS_STREAMING) {
		return;
	}
	if (access == SDL_TEXTUREACCESS_STATIC) { // Don't know what to do with it :(
		std::cout << "Texture was created with the Texture Access of Static -> Fix This" << std::endl;
		return;
	}
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
