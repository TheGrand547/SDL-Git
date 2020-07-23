#pragma once
#ifndef SPRITE_SHEET_H
#define SPRITE_SHEET_H
#include<map>
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
		std::map<std::string, Animation> animations;
		std::string key;
		Texture frame;
		Uint width, height, maxX, maxY;
	public:
		SpriteSheet(SDL_Renderer* renderer, const std::string& filename, int width, int height);
		~SpriteSheet();
		bool draw(std::string tag, SDL_Renderer* renderer, Point position, EntityDir dir);
		void addAnimation(std::string tag, Uint startingIndex, Uint endingIndex, Uint interval);
};
#endif
