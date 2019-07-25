#pragma once
#include<iostream>
#include<SDL2_ttf/SDL_ttf.h>
class Font {
	private:
		int fontSize;
		TTF_Font* fontRenderer;
		std::string filename;
	public:
		Font(int size = 20, std::string filename = "font.ttf");
		~Font();
		Font& operator=(const Font& font);
		// TODO: Rename this to bring up to standard, also format the fucking declarations to standard
		void drawTexture(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect rect, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
		void renderText(int x, int y, std::string text, SDL_Renderer *renderer, SDL_Color color, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
		void renderTextWrapped(int x, int y, std::string text, SDL_Renderer *renderer, SDL_Color color, int maxWidth,SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
};
