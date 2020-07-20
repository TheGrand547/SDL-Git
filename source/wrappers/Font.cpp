#include "Font.h"

Font::Font(int size, std::string filename) {
	this->filename = "./resources/" + filename;
	fontSize = size;
	fontRenderer = TTF_OpenFont(this->filename.c_str(), size);
	if (!fontRenderer) {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
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

void Font::drawText(Point position, const std::string& text, SDL_Renderer* renderer, SDL_Color color, int maxWidth, SDL_COPY_EX_ARGS) {
	if (!fontRenderer) {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        return;
	}
	SDL_Surface* surface;
	if (maxWidth == -1) {
		surface = TTF_RenderText_Blended(fontRenderer, text.c_str(), color);
	} else {
		surface = TTF_RenderText_Blended_Wrapped(fontRenderer, text.c_str(), color, maxWidth);
	}
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
