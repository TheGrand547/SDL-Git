#pragma once
#ifndef APPEARING_TEXT_H
#define APPEARING_TEXT_H
#include<SDL2/SDL.h>
#include<SDL2_ttf/SDL_ttf.h>
#include "wrappers/Font.h"
#include "wrappers/Timer.h"
#include "primitives/Point.h"
#include "essential/constants.h"

class AppearingText {
	private:
		Point position;
		SDL_Color color;
		std::string text;
		int ticksPerLetter, index, leftOver, charWrap;
		Timer timer;
		Font* font;
	public:
		AppearingText(std::string text, float lettersPerSecond, int startingIndex = 0, int fontSize = 20, std::string fileName = "resources/Font.ttf", SDL_Color color = COLORS::RED, Point position = Point(0, 0), int charWrap = 0);
		AppearingText(std::string text, float lettersPerSecond, int startingIndex, Point position, SDL_Color color, Font* font, int charWrap);
		~AppearingText();
		void update(SDL_Renderer* renderer);
};
#endif
