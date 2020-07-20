#pragma once
#ifndef FONT_H
#define FONT_H
#include<iostream>
#include<SDL_ttf.h>
#include "../essential/SDL_Headers.h"
#include "../primitives/Point.h"

class Font {
	protected:
		int fontSize;
		TTF_Font* fontRenderer;
		std::string filename;
	public:
		Font(int size = 20, std::string filename = "font.ttf");
		~Font();
		Font& operator=(const Font& font);
		void drawText(Point position, const std::string& text, SDL_Renderer* renderer, SDL_Color color, int maxWidth = -1, SDL_COPY_EX_ARGS_DEFAULTS);
};
#endif
