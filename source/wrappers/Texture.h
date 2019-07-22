#pragma once
#include<iostream>
#include<SDL2/SDL.h>
#include<SDL2/SDL2_rotozoom.h>
#include<SDL2_image/SDL_image.h>
#include "../primitives/Point.h"
#include "../essential/constants.h"
typedef Uint8 uint8_t;

class Texture {
	protected:
		int xpos, ypos;
		SDL_Texture *texture;
	public:
		Texture();
		~Texture();
		Texture &operator=(const Texture& that);
		Texture(const Texture& that);
		void free();
		SDL_Surface* scaleToCoords(SDL_Surface* surf, float desiredWidth, float desiredHeight);
		void setColor(Uint8 red, Uint8 green, Uint8 blue);
		void setAlpha(Uint8 alpha);
		void render(int x, int y, SDL_Renderer* renderer, SDL_Rect* clip = NULL, double angle = 0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
		void render(SDL_Renderer *renderer, SDL_Rect* clip = NULL, double angle = 0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
		void render(SDL_Renderer* renderer, Point offset);
		void renderAt(SDL_Renderer* renderer, Point position, Point offset);
		bool isLoaded();
		void createBlank(SDL_Renderer *renderer, int w, int h, uint32_t color = 0x0000000FF);
		SDL_Texture* getTexture();
		void setPos(int x = 0, int y = 0);
		void setPos(Point point) ;
		void loadFromFile(std::string path, SDL_Renderer* renderer, int xSize, int ySize, Uint8 r = 0x00, Uint8 g = 0x00, Uint8 b = 0x00);
};
