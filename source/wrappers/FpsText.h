#pragma once
#ifndef FPS_TEXT_H
#define FPS_TEXT_H
#include "Font.h"
#include "Timer.h"
#include "../primitives/Point.h"

class FpsText {
	protected:
		Font font;
		Point position;
		SDL_Color color;
		Timer fpsTimer, frameTimer;
	public:
		FpsText(Font& font, Point position, SDL_Color color);
		~FpsText();
		double getFps() const;
		void draw(Renderer renderer);
		void drawFrameTime(Renderer renderer);
};
#endif
