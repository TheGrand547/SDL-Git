#pragma once
#ifndef SPRITE_SHEET_H
#define SPRITE_SHEET_H
#include<string>
#include "../primitives/Point.h"
#include "../game_entities/base/ThingBase.h"

class SpriteSheet;

#include "Animation.h"
#include "Texture.h"
#include "Timer.h"

typedef uint Uint;
typedef ENTITY_DIRECTION EntityDir;

class SpriteSheet {
	private:
		Texture frame;
		Uint width, height, maxX, maxY;
	public:
		SpriteSheet(const std::string& filename, int width, int height, SDL_Renderer* renderer);
		~SpriteSheet();
		void draw(SDL_Renderer* renderer, Point position, EntityDir dir, Uint index);
};
#endif
