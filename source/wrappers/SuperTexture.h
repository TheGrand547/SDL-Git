#pragma once
#include<SDL2/SDL.h>
#include<SDL2/SDL2_gfxPrimitives.h>
#include<SDL2/SDL2_rotozoom.h>
#include<SDL2_image/SDL_image.h>
#include<SDL2_ttf/SDL_ttf.h>
#include "../primitives/Line.h"
#include "../primitives/Point.h"
#include "../primitives/Rect.h"
#include "../MyBase.h"
#include "../essential/util.h"
#include "Texture.h"

/* TODO: Add support for rendering another image onto this one, from file, texture or supertexture */

typedef Uint8 uint8_t;
class SuperTexture : public Texture, public MyBase {
	protected:
		int clipX, clipY;
	 public:
		int modified;
		SuperTexture(Uint8 r = 0x00, Uint8 g = 0x00, Uint8 b = 0x00, Uint8 a = 0xFF);
		~SuperTexture();
		void setClip(int xClip, int yClip);
		SDL_Texture* getBlank(SDL_Renderer* renderer);
		Point getOffset();
		void drawRect(SDL_Renderer* renderer, Rect rect);
		void drawBox(SDL_Renderer* renderer, Rect rect, SDL_Color color);
		void drawLine(SDL_Renderer* renderer, Point pointA, Point pointB);
		void render(SDL_Renderer* renderer, Point offset = Point(0, 0));
};
