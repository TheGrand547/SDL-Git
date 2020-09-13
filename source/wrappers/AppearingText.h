#pragma once
#ifndef APPEARING_TEXT_H
#define APPEARING_TEXT_H
#include<SDL.h>
#include<SDL_ttf.h>
#include "Text.h"
#include "Timer.h"
#include "../primitives/Point.h"
#include "../essential/constants.h"

typedef uint Uint;

// TODO: Combine AppearingText and AlertText
class AppearingText : public Text {
	private:
		int charWrap, leftOver, ticksPerLetter;
		Point position;
		SDL_Color color;
		std::string text;
		Timer timer;
		Uint index;
	public:
		AppearingText(std::string text, Point position, double lettersPerSecond, SDL_Color color, int charWrap = -1, int startingIndex = 0);
		~AppearingText();
		bool finished() const override;
		void draw(Renderer renderer) override;
		void setCharacterWrap(int wrap);
};
#endif
