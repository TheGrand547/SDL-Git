#pragma once
#ifndef TEXT_H
#define TEXT_H
#include "Font.h"

// Base class for all text related things so there can be a text container

class Text {
	protected:
		Font font;
	public:
		virtual ~Text() {}
		virtual bool finished() const = 0;
		virtual void draw(SDL_Renderer* renderer, Point offset) = 0;
		
		void setFont(const Font& font) {
			this->font = font;
		}
		void setFont(Font&& font) {
			this->font = font;
		}
};
#endif
