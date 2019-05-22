#pragma once
#ifndef FPS_TEXT_H
#define FPS_TEXT_H
#include "Font.h"
#include "Timer.h"
#include "../primitives/Point.h"

class FpsText {
	private:
		Font* font;
		Point position;
		SDL_Color color;
		int countedFrames;
		float averageFps;
		Timer timer;
	public:
		FpsText(Font* font, Point position, SDL_Color color);
		~FpsText();
		float getFps();
		void draw(SDL_Renderer* renderer);
};
#endif
