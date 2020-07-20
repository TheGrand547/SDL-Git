#pragma once
#ifndef TEXT_H
#define TEXT_H
#inlcude "Font.h"

// Base class for all text related things so there can be a text container

class Text {
	protected:
		Font font;
	public:
		virtual ~Text() = 0;
		virtual void draw(SDL_Renderer* renderer, Point offset) = 0;
};

#endif
