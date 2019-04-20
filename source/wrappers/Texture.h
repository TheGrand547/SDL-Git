#pragma once
#include<iostream>
#include<SDL2/SDL.h>
#include<SDL2/SDL2_rotozoom.h>
#include<SDL2_image/SDL_image.h>
#include "../primatives/Point.h"
#include "../essential/constants.h"
typedef Uint8 uint8_t;

class Texture {
	protected:
		int *width, *height;
		int *xpos, *ypos;
		SDL_Texture *texture = NULL;
	public:
		Texture() {
			texture = NULL;
			width = new int(0);
			height = new int(0);
			xpos = new int(0);
			ypos = new int(0);
		}
		
		~Texture() {
			free();
			delete this->width;
			delete this->height;
			delete this->xpos;
			delete this->ypos;
		}
		
		Texture &operator=(const Texture &that) {
			width = new int(0);
			height = new int(0);
			xpos = new int(0);
			ypos = new int(0);
			*height = *(that.height);
			*width = *(that.width);
			*xpos = *(that.xpos);
			*ypos = *(that.ypos);
			texture = NULL;
		}
		
		Texture (const Texture &that) {
			width = new int(0);
			height = new int(0);
			xpos = new int(0);
			ypos = new int(0);
			*height = *(that.height);
			*width = *(that.width);
			*xpos = *(that.xpos);
			*ypos = *(that.ypos);
			texture = NULL;
		}
		
		void free() {
			if (texture != NULL) {
				SDL_DestroyTexture(texture);
				texture = NULL;	
			}
		}
		
		SDL_Surface* scaleToCoords(SDL_Surface *surf, float desiredWidth, float desiredHeight) {
			double xFactor = desiredWidth / surf->w;
			double yFactor = desiredHeight / surf->h;
			return rotozoomSurfaceXY(surf, 0, xFactor, yFactor, 1);
		}
		
		void setColor(Uint8 red, Uint8 green, Uint8 blue) {
			SDL_SetTextureColorMod(this->texture, red, green, blue);
		}
		
		void setAlpha(Uint8 alpha) {
			SDL_SetTextureAlphaMod(this->texture, alpha);
		}
		
		void render(int x, int y, SDL_Renderer *renderer, SDL_Rect* clip=NULL, double angle=0, 
					SDL_Point* center=NULL, SDL_RendererFlip flip = SDL_FLIP_NONE) {
			SDL_Rect renderQuad = {x, y, *width, *height};
			if( clip != NULL ) {
				renderQuad.w = clip->w;
				renderQuad.h = clip->h;
			}
			SDL_RenderCopyEx(renderer, texture, clip, &renderQuad, angle, center, flip);
		}
		
		void render(SDL_Renderer *renderer, SDL_Rect* clip=NULL, double angle=0, 
					SDL_Point* center=NULL, SDL_RendererFlip flip = SDL_FLIP_NONE) {
			render(*(this->xpos)-1, *(this->ypos)-1, renderer, clip, angle, center, flip);
		}
		
		void render(SDL_Renderer* renderer, Point offset) {
			Rect temp = Rect(Point(*this->xpos, *this->ypos), *this->width, *this->height);
			Rect tempScreen = Rect(offset, Screen::SCREEN_WIDTH, Screen::SCREEN_HEIGHT);
			if (temp.overlap(tempScreen)){
				this->render(*(this->xpos)-offset.x()-1, *(this->ypos)-offset.y()-1, renderer);
			}
		}
		
		bool isLoaded() {
			return texture != NULL;
		}
		
		void createBlank(SDL_Renderer *renderer, int w, int h) {
			SDL_Texture *toReturn = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, w, h);
			SDL_Texture *tempText = NULL;
			SDL_Surface *tempSurf = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);
			if (tempSurf != NULL) {
				SDL_FillRect(tempSurf, NULL, 0x000000FF);
				SDL_SetRenderTarget(renderer, toReturn);
				tempText = SDL_CreateTextureFromSurface(renderer, tempSurf);
				SDL_RenderCopy(renderer, tempText, NULL, NULL);
				SDL_SetRenderTarget(renderer, NULL);
				
				SDL_DestroyTexture(tempText);
				*this->width = tempSurf->w;
				*this->height = tempSurf->h;
				this->texture = toReturn;
			}
			SDL_FreeSurface(tempSurf);
		}
		
		SDL_Texture* getTexture() {
			return this->texture;
		}
		
		void setPos(int x = 0, int y = 0) {
			*(this->xpos) = x;
			*(this->ypos) = y;
		}
		
		void setPos(Point point) {
			*(this->xpos) = point.x();
			*(this->ypos) = point.y();
		}
		
		void setPos(Point *point) {
			*(this->xpos) = point->x();
			*(this->ypos) = point->y();
		}
		
		void loadFromFile(std::string path, SDL_Renderer* renderer, int xSize, int ySize, Uint8 r = 0x00, Uint8 g = 0x00, Uint8 b = 0x00) {
			SDL_Texture *newTexture = NULL;
			SDL_Surface *tempSurface = IMG_Load(path.c_str());	
			SDL_Texture *tempTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, 100, 100);
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
				} else {
					width = new int(tempSurface->w);
					height = new int(tempSurface->h);
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
};
