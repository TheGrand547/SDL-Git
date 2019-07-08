#include "SuperTexture.h"

SuperTexture::SuperTexture(Uint8 r, Uint8 g, Uint8 b, Uint8 a) : Texture(), MyBase(r, g, b, a) {
	this->clipX = 0;
	this->clipY = 0;
}

SuperTexture::~SuperTexture() {}

void SuperTexture::setClip(int xClip, int yClip) {
	this->clipX = xClip;
	this->clipY = yClip;
}

SDL_Texture* SuperTexture::getBlank(SDL_Renderer* renderer) {
	return SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, this->clipX + 1, this->clipY + 1);
}

Point SuperTexture::getOffset() {
	return Point();
}

void SuperTexture::drawRect(SDL_Renderer* renderer, Rect rect) {
	SDL_Texture* tempTexture = this->getBlank(renderer);
	SDL_SetRenderTarget(renderer, tempTexture);
	SDL_RenderCopy(renderer, this->texture, NULL, NULL);
	rect.superDraw(renderer, this->getOffset());
	SDL_SetRenderTarget(renderer, NULL);
	this->texture = tempTexture;
}

void SuperTexture::drawBox(SDL_Renderer* renderer, Rect rect, SDL_Color color) {
	SDL_Texture* tempTexture = this->getBlank(renderer);
	SDL_SetRenderTarget(renderer, tempTexture);
	SDL_RenderCopy(renderer, this->texture, NULL, NULL);
	boxRGBA(renderer, Point(0, 0), rect.getBottomRight(), color.r, color.g, color.b, color.a);
	SDL_SetRenderTarget(renderer, NULL);
	this->texture = tempTexture;
}

void SuperTexture::drawLine(SDL_Renderer* renderer, Point pointA, Point pointB) {
	SDL_Texture* tempTexture = this->getBlank(renderer);
	SDL_SetRenderTarget(renderer, tempTexture);
	SDL_RenderCopy(renderer, this->texture, NULL, NULL);
	Line temp = Line(pointA, pointB);
	temp.setColorChannels(this);
	temp.drawLine(renderer, this->getOffset());
	SDL_SetRenderTarget(renderer, NULL);
	this->texture = tempTexture;
}

void SuperTexture::render(SDL_Renderer* renderer, Point offset) {
	Texture::render(renderer, offset);
}
