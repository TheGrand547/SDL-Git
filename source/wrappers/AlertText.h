#pragma once
#ifndef ALERT_TEXT_H
#define ALERT_TEXT_H
#include "../primitives/Point.h"
#include "Text.h"
#include "Timer.h"
#include<string>
#include<SDL2/SDL.h>

// TODO: Maybe 
class AlertText : public Text {
	protected:
		bool done;
		float duration;
		Point position;
		SDL_Color color;
		std::string message;
		Timer timer;
	public:
		AlertText(const std::string& text, Point position, SDL_Color color, int textSize = 20, float ms = 1000, const std::string& filename = "resources/font.ttf");
		~AlertText();
		bool finished() const override;
		void draw(SDL_Renderer* renderer, Point offset) override;
};
#endif
