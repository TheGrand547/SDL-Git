#pragma once
#ifndef FONT_H
#define FONT_H
#include "../essential/log.h"
#include "../essential/SDL_Headers.h"
#include "../primitives/Point.h"
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>

class Font {
	protected:
		int size;
		TTF_Font* font;
		std::string name;
	public:
		Font(int size = 20, const std::string& filename = "resources/fonts/default.ttf");
		Font(const Font& font);
		Font(Font&& font);
		~Font();
		Font& operator=(const Font& font);
		Font& operator=(Font&& font);
		void closeFont();
		void drawText(Point position, const std::string& text, SDL_Renderer* renderer, SDL_Color color, int maxWidth = -1, SDL_COPY_EX_ARGS_DEFAULTS);
		void loadFont(int size, const std::string& filename);
};
#endif
