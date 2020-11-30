#pragma once
#ifndef TEXT_H
#define TEXT_H
#include "Font.h"

// Base class for all text related things so there can be a text container
class Text {
	protected:
		// TODO: Add the attribute stuff
		Font font;
		SDL_Color color;
	public:
		Text();
		template<typename T> Text(T f) : font(std::forward<Font>(f)) {}
		template<typename T> Text(T f, SDL_Color color) : font(std::forward<Font>(f)), color(color) {}
		virtual ~Text();
		virtual bool finished() const = 0;
		virtual void draw(Renderer renderer) = 0;
		virtual void setColor(SDL_Color color);

		template<typename T> void setFont(T font) {
			this->font = std::forward<Font>(font);
		}
};
#endif
