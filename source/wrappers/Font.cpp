#include "Font.h"

Font::Font(int size, const std::string& name) : size(size), name(name) {
	this->loadFont(size, name);
}

Font::~Font() {
	this->closeFont();
}

Font::Font(const Font& font) : size(font.size), name(font.name) {
	this->loadFont(this->size, this->name);
}

Font::Font(Font&& font) : size(font.size), font(font.font), name(font.name) {
	font.font = NULL;
	font.size = 0;
	font.name = "";
}

Font& Font::operator=(const Font& font) {
	if (this != &font) {
		this->closeFont();
		this->name = font.name;
		this->size = font.size;
		if (!strcmp(this->name.c_str(), "resources/font.ttf")) this->font = TTF_OpenFont("resources/font.ttf", font.size);
		else this->font = TTF_OpenFont(font.name.c_str(), font.size);
	}
	return *this;
}

Font& Font::operator=(Font&& font) {
	this->closeFont();
	this->size = font.size;
	this->name = font.name;
	this->font = font.font;
	font.font = NULL;
	return *this;
}

void Font::closeFont() {
	if (this->font != NULL) {
		TTF_CloseFont(this->font);
		this->font = NULL;
		this->size = 0;
		this->name = "";
	}
}

void Font::drawText(Point position, const std::string& text, SDL_Renderer* renderer, SDL_Color color, int maxWidth, SDL_COPY_EX_ARGS) {
	if (!this->font) {
        LOG("TTF_OpenFont: %s\n", TTF_GetError());
        return;
	}
	SDL_Surface* surface;
	if (maxWidth == -1) surface = TTF_RenderText_Blended(font, text.c_str(), color);
	else surface = TTF_RenderText_Blended_Wrapped(font, text.c_str(), color, maxWidth);
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

void Font::loadFont(int size, const std::string& name) {
	this->name = name;
	this->size = size;
	this->font = TTF_OpenFont(this->name.c_str(), size);
	if (!this->font) LOG("TTF_OpenFont: %s\n", TTF_GetError());
}
