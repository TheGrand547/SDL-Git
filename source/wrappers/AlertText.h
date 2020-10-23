#pragma once
#ifndef ALERT_TEXT_H
#define ALERT_TEXT_H
#include "../primitives/Point.h"
#include "Text.h"
#include "Timer.h"
#include <SDL2/SDL.h>
#include <string>

typedef uint Uint;

// TODO: Maybe 
class AlertText : public Text {
	protected:
		bool done;
		Uint duration;
		Point position;
		SDL_Color color;
		std::string message;
		Timer timer;
	public:
		AlertText(const std::string& text, Point position, SDL_Color color, int ms);
		AlertText(const std::string& text, Point position, SDL_Color color, int ms, Font& font);
		~AlertText();
		bool finished() const override;
		void draw(Renderer renderer) override;
};
#endif
