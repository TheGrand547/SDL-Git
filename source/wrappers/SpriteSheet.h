#pragma once
#ifndef SPRITE_SHEET_H
#define SPRITE_SHEET_H
#include "../primitives/Point.h"
#include "../game_entities/base/ThingBase.h"

class SpriteSheet;

#include "Texture.h"
#include "Timer.h"
#include <map>
#include <string>

typedef uint Uint;
typedef ENTITY_DIRECTION EntityDir;

class SpriteSheet {
	protected:
		class Animation {
			private:
				bool started;
				Timer timer;
				Uint endingIndex, interval, startingIndex;
			public:
				Uint currentIndex;

				Animation(Uint startingIndex = 0, Uint endingIndex = 0, Uint interval = 0);
				Animation(const Animation& other);
				~Animation();
				Animation& operator=(const Animation& other);
				bool isReal() const;
				bool update();
				bool isStarted() const;
				void exit();
				void pause();
				void start();
				void reset(); // Alias of start to be more specific
		};
		std::map<std::string, SpriteSheet::Animation> animations;
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
