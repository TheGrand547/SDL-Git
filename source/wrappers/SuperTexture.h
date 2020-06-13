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

typedef uint8_t Uint8; 

class SuperTexture : public Texture, public MyBase {
	protected:
	 public:
		SuperTexture(Uint8 r = 0x00, Uint8 g = 0x00, Uint8 b = 0x00, Uint8 a = 0xFF);
		~SuperTexture();
		Point getOffset();
		void drawRect(SDL_Renderer* renderer, Rect rect);
		void drawBox(SDL_Renderer* renderer, Rect rect, SDL_Color color);
		void drawLine(SDL_Renderer* renderer, Point pointA, Point pointB);
};
