#include "SuperTexture.h"

SuperTexture::SuperTexture(Uint8 r, Uint8 g, Uint8 b, Uint8 a) : Texture(), MyBase(r, g, b, a) {}

SuperTexture::~SuperTexture() {}

SDL_Texture* SuperTexture::getBlank(SDL_Renderer* renderer) {
	return SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, this->width, this->height);
}

Point SuperTexture::getOffset() {
	return Point(0, 0);
}

void SuperTexture::drawRect(SDL_Renderer* renderer, Rect rect) {
	if (this->texture == NULL) return;
	SDL_Texture* tempTexture = this->getBlank(renderer);
	SDL_SetRenderTarget(renderer, tempTexture);
	SDL_RenderCopy(renderer, this->texture, NULL, NULL);
	rect.superDraw(renderer, this->getOffset());
	SDL_SetRenderTarget(renderer, NULL);
	this->texture = tempTexture;
}

void SuperTexture::drawBox(SDL_Renderer* renderer, Rect rect, SDL_Color color) {
	if (this->texture == NULL) return;
	SDL_Texture* tempTexture = this->getBlank(renderer);
	SDL_SetRenderTarget(renderer, tempTexture);
	SDL_RenderCopy(renderer, this->texture, NULL, NULL);
	boxRGBA(renderer, Point(0, 0), rect.getBottomRight(), color.r, color.g, color.b, color.a);
	SDL_SetRenderTarget(renderer, NULL);
	this->texture = tempTexture;
}

void SuperTexture::drawLine(SDL_Renderer* renderer, Point pointA, Point pointB) {
	if (this->texture == NULL) return;
	SDL_Texture* tempTexture = this->getBlank(renderer);
	SDL_SetRenderTarget(renderer, tempTexture);
	SDL_RenderCopy(renderer, this->texture, NULL, NULL);
	Line temp = Line(pointA, pointB);
	//temp.setColorChannels(this);
	temp.drawLine(renderer, this->getOffset());
	SDL_SetRenderTarget(renderer, NULL);
	this->texture = tempTexture;
}
