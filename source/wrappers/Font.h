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
		int fontSize;
		TTF_Font* fontRenderer;
		std::string filename;
	public:
		Font(int size = 20, const std::string& filename = "resources/font.ttf");
		// TODO: COPY CONSTRUCTOR
		~Font();
		Font& operator=(const Font& font);
		Font& operator=(Font&& font);
		void drawText(Point position, const std::string& text, SDL_Renderer* renderer, SDL_Color color, int maxWidth = -1, SDL_COPY_EX_ARGS_DEFAULTS);
		void loadFont(int size, const std::string& filename);
};
#endif
