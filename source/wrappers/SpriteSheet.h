#pragma once
#ifndef SPRITE_SHEET_H
#define SPRITE_SHEET_H
#include<string>
#include<vector>
#include "../primitives/Point.h"
#include "Texture.h"
#include "Timer.h"

typedef uint Uint;

class SpriteSheet {
	private:
		Timer t;
		Texture frame;
		Uint width, height, currentX, currentY, maxX, maxY;
	public:
		SpriteSheet(const std::string& filename, int width, int height, SDL_Renderer* renderer);
		~SpriteSheet();
		void draw(SDL_Renderer* renderer, Point position);
		void drawTo(SDL_Renderer* renderer, Texture& fo);
};
#endif
