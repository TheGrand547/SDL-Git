#pragma once
#ifndef APPEARING_TEXT_H
#define APPEARING_TEXT_H
#include<SDL.h>
#include<SDL_ttf.h>
#include "Font.h"
#include "Timer.h"
#include "../primitives/Point.h"
#include "../essential/constants.h"

/* TODO: Make the Constructor not a massive mistake */
class AppearingText {
	private:
		Point position;
		SDL_Color color;
		std::string text;
		int ticksPerLetter, leftOver, charWrap;
		uint index;
		Timer timer;
		Font* font;
	public:
		AppearingText(std::string text, Font* font, Point position, double lettersPerSecond, SDL_Color color, int charWrap = 0, int startingIndex = 0);
		~AppearingText();
		void update(SDL_Renderer* renderer);
		void setCharacterWrap(int wrap);
};
#endif
