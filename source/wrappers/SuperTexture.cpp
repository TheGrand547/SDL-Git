#include "SuperTexture.h"

SuperTexture::SuperTexture(Uint8 r, Uint8 g, Uint8 b, Uint8 a) : Texture(), Color(r, g, b, a) {}

SuperTexture::~SuperTexture() {}

void SuperTexture::drawRect(SDL_Renderer* renderer, Rect rect) {
	if (this->texture == NULL) return;
	SDL_Texture* tempTexture = this->getBlankRenderTarget(renderer);
	SDL_SetRenderTarget(renderer, tempTexture);
	SDL_RenderCopy(renderer, this->texture, NULL, NULL);
	rect.superDraw(renderer, Point(0,0));
	SDL_SetRenderTarget(renderer, NULL);
	this->texture = tempTexture;
}

void SuperTexture::drawBox(SDL_Renderer* renderer, Rect rect, SDL_Color color) {
	if (this->texture == NULL) return;
	SDL_Texture* tempTexture = this->getBlankRenderTarget(renderer);
	SDL_SetRenderTarget(renderer, tempTexture);
	SDL_RenderCopy(renderer, this->texture, NULL, NULL);
	boxRGBA(renderer, Point(0, 0), rect.getBottomRight(), color.r, color.g, color.b, color.a);
	SDL_SetRenderTarget(renderer, NULL);
	this->texture = tempTexture;
}

void SuperTexture::drawLine(SDL_Renderer* renderer, Point pointA, Point pointB) {
	if (this->texture == NULL) return;
	SDL_Texture* tempTexture = this->getBlankRenderTarget(renderer);
	SDL_SetRenderTarget(renderer, tempTexture);
	SDL_RenderCopy(renderer, this->texture, NULL, NULL);
	Line temp = Line(pointA, pointB);
	//temp.setColorChannels(this);
	temp.drawLine(renderer, Point(0,0));
	SDL_SetRenderTarget(renderer, NULL);
	this->texture = tempTexture;
}
