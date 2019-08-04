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

void Texture::setColorMod(Uint8 red, Uint8 green, Uint8 blue) {
	SDL_SetTextureColorMod(this->texture, red, green, blue);
}

void Texture::setAlpha(Uint8 alpha) {
	SDL_SetTextureAlphaMod(this->texture, alpha);
}

void Texture::setBlend(SDL_BlendMode mode) {
	SDL_SetTextureBlendMode(this->texture, mode);
}

void Texture::setColorKey(Uint8 red, Uint8 green, Uint8 blue) { // Modified from lazyfoo.net
	this->setBlend(SDL_BLENDMODE_BLEND);
	void* rawPixels;
	int pitch, width, height;
	Uint32 format;
	if (SDL_LockTexture(this->texture, NULL, &rawPixels, &pitch) != 0) {
		return;
	}
	SDL_QueryTexture(this->texture, &format, NULL, &width, &height);
	SDL_PixelFormat* mappingFormat = SDL_AllocFormat(format);
	Uint32* pixels = (Uint32*)rawPixels;
	int pixelCount = (pitch / 4) * height;
	Uint32 colorKey = SDL_MapRGB(mappingFormat, red, green, blue);
	Uint32 transparent = SDL_MapRGBA(mappingFormat, 0xFF, 0xFF, 0xFF, 0x00);
	for (int i = 0; i < pixelCount; ++i) {
		if (pixels[i] == colorKey) {
			pixels[i] = transparent;
		}
	}
	SDL_UnlockTexture(this->texture);
	SDL_FreeFormat(mappingFormat);
}

void Texture::draw(int x, int y, SDL_Renderer* renderer, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip) {
	int width, height;
	SDL_QueryTexture(this->texture, NULL, NULL, &width, &height);
	SDL_Rect renderQuad = {x, y, width, height};
	if (clip != NULL) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	SDL_RenderCopyEx(renderer, texture, clip, &renderQuad, angle, center, flip);
}

void Texture::draw(SDL_Renderer* renderer, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip) {
	this->draw(this->xpos - 1, this->ypos - 1, renderer, clip, angle, center, flip);
}

void Texture::draw(SDL_Renderer* renderer, Point offset) {
	this->draw((this->xpos - offset.x()) - 1, (this->ypos - offset.y()) - 1, renderer);
}

void Texture::drawAt(SDL_Renderer* renderer, Point position, Point offset) {
	this->setPos(position);
	this->draw(renderer, offset);
}

bool Texture::isLoaded() {
	return texture != NULL;
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
