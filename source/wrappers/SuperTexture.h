#pragma once
#include<SDL2/SDL.h>
#include<SDL2/SDL2_gfxPrimitives.h>
#include<SDL2/SDL2_rotozoom.h>
#include<SDL2_image/SDL_image.h>
#include<SDL2_ttf/SDL_ttf.h>
#include "../primatives/Line.h"
#include "../primatives/Point.h"
#include "../primatives/Rect.h"
#include "../MyBase.h"
#include "../essential/util.h"
#include "Texture.h"

typedef Uint8 uint8_t;
class SuperTexture : public Texture, public MyBase {
	protected:
		int* clipX = NULL;
		int* clipY = NULL;
	public:
		SuperTexture(Uint8 r = 0x00, Uint8 g = 0x00, Uint8 b = 0x00, Uint8 a = 0xFF) : Texture(), MyBase(r, g, b, a) {
			this->clipX = new int(0);
			this->clipY = new int(0);
		}
		
		~SuperTexture() {
			delete this->clipX;
			delete this->clipY;
		}
		
		void setClip(int xClip, int yClip) {
			this->clipX = new int(xClip);
			this->clipY = new int(yClip);
		}
		
		void reBound() {
			*this->width = *clipX+1;
			*this->height = *clipY+1;
		}
		
		SDL_Texture* getBlank(SDL_Renderer* renderer) {
			return SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, *clipX+1, *clipY+1);
		}
		
		Point getOffset() {
			return Point(*this->xpos-1, *this->ypos-1);
		}
		
		void drawRect(SDL_Renderer* renderer, Rect* rect) {
			SDL_Texture* tempTexture = this->getBlank(renderer);
			SDL_SetRenderTarget(renderer, tempTexture);
			SDL_RenderCopy(renderer, this->texture, NULL, NULL);
			rect->draw(renderer, this->getOffset());
			SDL_SetRenderTarget(renderer, NULL);
			this->texture = tempTexture;
		}
		
		void drawRect(SDL_Renderer* renderer, Rect rect) {
			SDL_Texture* tempTexture = this->getBlank(renderer);
			SDL_SetRenderTarget(renderer, tempTexture);
			SDL_RenderCopy(renderer, this->texture, NULL, NULL);
			rect.draw(renderer, this->getOffset());
			SDL_SetRenderTarget(renderer, NULL);
			this->texture = tempTexture;
		}
		
		void drawBox(SDL_Renderer* renderer, Rect* rect) {
			SDL_Texture* tempTexture = this->getBlank(renderer);
			SDL_SetRenderTarget(renderer, tempTexture);
			SDL_RenderCopy(renderer, this->texture, NULL, NULL);
			//TEMPORARY LINE BEWARE
			boxRGBA(renderer, Point(0, 0), *rect->getBottomRight()-this->getOffset(), 0xFF, 0x00, 0x00, 0xFF);
			SDL_SetRenderTarget(renderer, NULL);
			this->texture = tempTexture;
		}
		
		void drawBox(SDL_Renderer* renderer, Rect rect) {
			SDL_Texture* tempTexture = this->getBlank(renderer);
			SDL_SetRenderTarget(renderer, tempTexture);
			SDL_RenderCopy(renderer, this->texture, NULL, NULL);
			//TEMPORARY LINE BEWARE
			boxRGBA(renderer, Point(0, 0), *rect.getBottomRight()-this->getOffset(), 0xFF, 0x00, 0x00, 0xFF);
			SDL_SetRenderTarget(renderer, NULL);
			this->texture = tempTexture;
		}
		
		void drawLine(SDL_Renderer* renderer, Line* line) {
			SDL_Texture* tempTexture = this->getBlank(renderer);
			SDL_SetRenderTarget(renderer, tempTexture);
			SDL_RenderCopy(renderer, this->texture, NULL, NULL);
			line->drawLine(renderer, this->getOffset());
			SDL_SetRenderTarget(renderer, NULL);
			this->texture = tempTexture;
		}
		
		void drawLine(SDL_Renderer* renderer, Point pointA, Point pointB) {
			SDL_Texture* tempTexture = this->getBlank(renderer);
			SDL_SetRenderTarget(renderer, tempTexture);
			SDL_RenderCopy(renderer, this->texture, NULL, NULL);
			Line temp = Line(pointA, pointB);
			temp.setColorChannels(this);
			temp.drawLine(renderer, this->getOffset());
			SDL_SetRenderTarget(renderer, NULL);
			this->texture = tempTexture;
		}
		
		void render(SDL_Renderer* renderer){
			reBound();
			Texture::render(renderer);
		}
		
		void render(SDL_Renderer* renderer, Point offset) {
			reBound();
			Texture::render(renderer, offset);
		}
};
