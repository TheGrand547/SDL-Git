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
	double xFactor = desiredWidth / surf->w;
	double yFactor = desiredHeight / surf->h;
	return rotozoomSurfaceXY(surf, 0, xFactor, yFactor, 1);
}

void Texture::setColor(Uint8 red, Uint8 green, Uint8 blue) {
	SDL_SetTextureColorMod(this->texture, red, green, blue);
}

void Texture::setAlpha(Uint8 alpha) {
	SDL_SetTextureAlphaMod(this->texture, alpha);
}

void Texture::draw(int x, int y, SDL_Renderer* renderer, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip) {
	int width, height;
	SDL_QueryTexture(this->texture, NULL, NULL, &width, &height);
	SDL_Rect renderQuad = {x, y, width, height};
	if( clip != NULL) {
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

void Texture::loadFromFile(std::string path, SDL_Renderer* renderer, int xSize, int ySize, Uint8 r, Uint8 g, Uint8 b) {
	SDL_Texture* newTexture = NULL;
	SDL_Surface* tempSurface = IMG_Load(path.c_str());	
	SDL_Texture* tempTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, 100, 100);
	if (tempSurface == NULL) {
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	} else {
		SDL_SetColorKey(tempSurface, SDL_TRUE, SDL_MapRGB( tempSurface->format, r, g, b));
		if (xSize > 0 && ySize > 0) {
			tempSurface = scaleToCoords(tempSurface, xSize, ySize);
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
}
