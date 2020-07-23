#include "Font.h"

Font::Font(int size, const std::string& filename) {
	this->loadFont(size, filename);
}

Font::~Font() {
	if (this->fontRenderer != NULL) TTF_CloseFont(this->fontRenderer);
	fontRenderer = NULL;
}

Font& Font::operator=(const Font& font) {
	if (this != &font) {
		this->filename = font.filename;
		this->fontSize = font.fontSize;
		if (this->fontRenderer != NULL) {				
			TTF_CloseFont(fontRenderer);
			fontRenderer = NULL;
		}
		if (!strcmp(this->filename.c_str(), "resources/font.ttf")) this->fontRenderer = TTF_OpenFont("resources/font.ttf", font.fontSize);
		else this->fontRenderer = TTF_OpenFont(font.filename.c_str(), font.fontSize);
	}
	return *this;
}

Font& Font::operator=(Font&& font) {
	this->fontSize = font.fontSize;
	this->filename = font.filename;
	if (this->fontRenderer != NULL) {	
		TTF_CloseFont(fontRenderer);
		fontRenderer = NULL;
	}
	this->fontRenderer = font.fontRenderer;
	font.fontRenderer = NULL;
	return *this;
}

void Font::drawText(Point position, const std::string& text, SDL_Renderer* renderer, SDL_Color color, int maxWidth, SDL_COPY_EX_ARGS) {
	if (!fontRenderer) {
        LOG("TTF_OpenFont: %s\n", TTF_GetError());
        return;
	}
	SDL_Surface* surface;
	if (maxWidth == -1) surface = TTF_RenderText_Blended(fontRenderer, text.c_str(), color);
	else surface = TTF_RenderText_Blended_Wrapped(fontRenderer, text.c_str(), color, maxWidth);
	if (surface) {
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
		if (texture) {
			SDL_Rect rect = {(int)position.x, (int)position.y, surface->w, surface->h};
			SDL_RenderCopyEx(renderer, texture, clip, &rect, angle, center, flip);
		}
		SDL_DestroyTexture(texture);
	}
	SDL_FreeSurface(surface);
}

void Font::loadFont(int size, const std::string& filename) {
	this->filename = filename;
	this->fontSize = size;
	this->fontRenderer = TTF_OpenFont(this->filename.c_str(), size);
	if (!this->fontRenderer) LOG("TTF_OpenFont: %s\n", TTF_GetError());
}
