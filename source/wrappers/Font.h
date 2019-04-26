#pragma once
#include<iostream>
#include<SDL2_ttf/SDL_ttf.h>
class Font {
	private:
		int *fontSize;
		TTF_Font *fontRenderer;
	public:
		Font(int size = 20, const char *filename = "resources/font.ttf") {
			fontSize = new int(size);
			fontRenderer = TTF_OpenFont(filename, size);
			if (fontRenderer == NULL) {
				printf("Failed to load font\n");
			}
		}
		
		~Font() {
			TTF_CloseFont(fontRenderer);
			fontRenderer = NULL;
			delete fontSize;
		}
		
		void drawTexture(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect rect, 
								SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, 
								SDL_RendererFlip flip = SDL_FLIP_NONE) {
			 SDL_RenderCopyEx(renderer, texture, clip, &rect, angle, center, flip);
		}
		
		void renderText(int x, int y, std::string text, SDL_Renderer *renderer, SDL_Color color, 
								SDL_Rect* clip = NULL, double angle = 0.0, 
								SDL_Point* center = NULL, 
								SDL_RendererFlip flip = SDL_FLIP_NONE) {
			SDL_Surface *surface = TTF_RenderText_Blended(fontRenderer, text.c_str(), color);
			if (!(surface == NULL)) {
				SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
				if (!(texture == NULL)) {
					SDL_FreeSurface(surface);
					SDL_Rect newRect = {x, y, surface->w, surface->h};
					drawTexture(renderer, texture, newRect, clip, angle, center, flip);
					SDL_DestroyTexture(texture);
				}
			}
		}
		
		void renderTextWrapped(int x, int y, std::string text, SDL_Renderer *renderer, SDL_Color color, int maxWidth,
								SDL_Rect* clip = NULL, double angle = 0.0, 
								SDL_Point* center = NULL, 
								SDL_RendererFlip flip = SDL_FLIP_NONE) {
									
									
			/* TESTING */
			/* removed for now cause its dumb
			std::string test = " ";
			std::size_t temp = 0;
			temp = text.rfind(test);
			if (temp != std::string::npos && temp < text.length()) {
				std::stringstream help;
				help.str(text);
				help << "------";
				int* tempX = new int(0);
				int* tempY = new int(0);
				TTF_SizeText(this->fontRenderer, help.str().c_str(), tempX, tempY);
				if (*tempX % maxWidth > maxWidth - maxWidth/4) {
					help.str("");
					for (int i = 0; i < text.length(); i++) {
						help << text[i];
						if (i == temp) {
							help << "\n";
						}
					}
					text = help.str();
				}
				delete tempX;
				delete tempY;
			}*/
			/*
			std::stringstream help;
			help.str(text);
			help << "--";
			int* tempX = new int(0);
			int* tempY = new int(0);
			TTF_SizeText(this->fontRenderer, help.str().c_str(), tempX, tempY);
			if (*tempX % maxWidth > maxWidth - maxWidth / 4) {
				std::string test = " ";
				std::size_t temp = 0;
				temp = text.rfind(test);
				if (temp != std::string::npos)
					text.insert(temp, "\n");
			}
			delete tempX;
			delete tempY;
			*/
			SDL_Surface *surface = TTF_RenderText_Blended_Wrapped(fontRenderer, text.c_str(), color, maxWidth);
			if (!(surface == NULL)) {
				SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
				if (!(texture == NULL)) {
					SDL_FreeSurface(surface);
					SDL_Rect newRect = {x, y, surface->w, surface->h};
					drawTexture(renderer, texture, newRect, clip, angle, center, flip);
					SDL_DestroyTexture(texture);
				}
			}
		}
};
