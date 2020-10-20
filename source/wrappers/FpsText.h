#pragma once
#ifndef FPS_TEXT_H
#define FPS_TEXT_H
#include "../primitives/Point.h"
#include "Font.h"
#include "Text.h"
#include "Timer.h"

class FpsText : public Text {
	protected:
		Font font;
		Point position;
		SDL_Color color;
		Timer fpsTimer, frameTimer;
	public:
		FpsText(Font& font, Point position, SDL_Color color);
		~FpsText();
		bool finished() const override;
		double getFps() const;
		void draw(Renderer renderer) override;
		void drawFrameTime(Renderer renderer);
};
#endif
