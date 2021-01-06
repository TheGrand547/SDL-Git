#pragma once
#ifndef APPEARING_TEXT_H
#define APPEARING_TEXT_H
#include "../essential/constants.h"
#include "../primitives/Point.h"
#include "Text.h"
#include "Timer.h"
#include <SDL.h>
#include <SDL_ttf.h>

typedef uint Uint;

// TODO: Make this a utility class that is addable to the other texts
// TODO: Combine AppearingText and AlertText
// TODO: Make this not shit
class AppearingText : public Text {
	private:
		int charWrap, leftOver, ticksPerLetter;
		Point position;
		SDL_Color color;
		std::string text;
		Timer timer;
		Uint index;
	public:
		AppearingText(const std::string& text, Point position, double lettersPerSecond, SDL_Color color, int charWrap = -1, int startingIndex = 0);
		AppearingText(const std::string& text, Point position, double lettersPerSecond, SDL_Color color, int charWrap, int startingIndex, const Font& font);
		AppearingText(const std::string& text, Point position, double lettersPerSecond, SDL_Color color, int charWrap, int startingIndex, Font&& font);
		~AppearingText();
		bool finished() const override;
		void draw(Renderer renderer) override;
		void setCharacterWrap(int wrap);
};
#endif
