#pragma once
#include<SDL.h>
#include<SDL2_gfxPrimitives.h>
#include<SDL2_rotozoom.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include "../primitives/Line.h"
#include "../primitives/Point.h"
#include "../primitives/Rect.h"
#include "../Color.h"
#include "../essential/util.h"
#include "Texture.h"


// TODO: Either revamp or remove this class
class SuperTexture : public Texture, public Color {
	 public:
		SuperTexture(Uint8 r = 0x00, Uint8 g = 0x00, Uint8 b = 0x00, Uint8 a = 0xFF);
		~SuperTexture();
		void drawRect(SDL_Renderer* renderer, Rect rect);
		void drawBox(SDL_Renderer* renderer, Rect rect, SDL_Color color);
		void drawLine(SDL_Renderer* renderer, Point pointA, Point pointB);
};
