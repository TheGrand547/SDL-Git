#pragma once
#ifndef ALERT_TEXT_H
#define ALERT_TEXT_H
#include "Font.h"
#include "Timer.h"
#include "../primitives/Point.h"
#include<string>
#include<SDL2/SDL.h>
class AlertText {
	private:
		Font font;
		SDL_Color color;
		Point position;
		std::string message;
		Timer timer;
		bool finished;
		float maxMilliseconds;
	public:
		AlertText(std::string text, Point position, SDL_Color color, int textSize = 20, float milliseconds = 1000, std::string filename = "font.ttf");
		~AlertText();
		bool isDone();
		void render();
};
#endif
