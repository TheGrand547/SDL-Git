#pragma once
#include<iostream>
#include<SDL2/SDL.h>
#include<SDL2/SDL2_rotozoom.h>
#include<SDL2_image/SDL_image.h>
#include "../primitives/Point.h"
#include "../essential/constants.h"
#include "../essential/log.h"
#include "../essential/random.h"
#include "../essential/SDLUtil.h"
#include "../essential/SDL_Headers.h"
#include "PixelMod.h"
typedef uint8_t Uint8;
typedef uint32_t Uint32;

class Texture {
	protected:
		int xpos, ypos;
		SDL_Texture* texture;
	public:
		Texture();
		~Texture();
		Texture& operator=(const Texture& that);
		Texture(const Texture& that);
		int getHeight();
		int getWidth();
		void free();
		void setAlpha(Uint8 alpha);
		void setBlend(SDL_BlendMode mode);
		void setColorMod(Uint8 red, Uint8 green, Uint8 blue);
		void setColorKey(Uint8 red, Uint8 green, Uint8 blue);
		void draw(Point pos, SDL_Renderer* renderer, SDL_COPY_EX_ARGS_DEFAULTS);
		void draw(int x, int y, SDL_Renderer* renderer, SDL_COPY_EX_ARGS_DEFAULTS);
		void draw(SDL_Renderer* renderer, SDL_Rect* clip = NULL, double angle = 0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
		void draw(SDL_Renderer* renderer, Point offset);
		void drawAt(SDL_Renderer* renderer, Point position, Point offset);
		bool isLoaded();
		bool notLoaded();
		void createBlank(SDL_Renderer* renderer, int w, int h, Uint32 color = 0x0000000FF);
		SDL_Texture* getTexture();
		void setPos(int x = 0, int y = 0);
		void setPos(Point point);
		void loadFromFile(std::string path, SDL_Renderer* renderer, int xSize = 0, int ySize = 0);
		void normalizeTexture(SDL_Renderer* renderer);
		//TODO: Add more functionality
		// Filters
		void bilateralFilter(const float valI, const float valS, const int kernelSize = 5, 
		        const int xStart = 2, const int yStart = 2, int width = 0, int height = 0);
		void dither();
		void testFilter();
		void floatyEdges();
};
