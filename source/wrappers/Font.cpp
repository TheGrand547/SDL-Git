#include "Font.h"

Font::Font(int size, std::string filename) {
	this->filename = "/resources/" + filename;
	fontSize = size;
	fontRenderer = TTF_OpenFont(this->filename.c_str(), size);
	if (fontRenderer == NULL) {
		printf("Failed to load font\n");
	}
}

Font::~Font() {
	if (this->fontRenderer != NULL) {
		TTF_CloseFont(this->fontRenderer);
	}
	fontRenderer = NULL;
}

Font& Font::operator=(const Font& font) {
	this->fontSize = font.fontSize;
	if (this->fontRenderer != NULL) {
		TTF_CloseFont(fontRenderer);
		fontRenderer = NULL;
	}
	
	this->fontRenderer = TTF_OpenFont(font.filename.c_str(), font.fontSize);
	return *this;
}

void Font::drawTexture(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect rect, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip) {
	 SDL_RenderCopyEx(renderer, texture, clip, &rect, angle, center, flip);
}

void Font::renderText(int x, int y, std::string text, SDL_Renderer *renderer, SDL_Color color, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip) {
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

void Font::renderTextWrapped(int x, int y, std::string text, SDL_Renderer *renderer, SDL_Color color, int maxWidth, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip) {
	SDL_Surface* surface = TTF_RenderText_Blended_Wrapped(fontRenderer, text.c_str(), color, maxWidth);
	if (surface != NULL) {
		SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
		if (!(texture == NULL)) {
			SDL_FreeSurface(surface);
			SDL_Rect newRect = {x, y, surface->w, surface->h};
			drawTexture(renderer, texture, newRect, clip, angle, center, flip);
			SDL_DestroyTexture(texture);
		}
	}
}
