#pragma once
#include<iostream>
#include<SDL2/SDL.h>
#include<SDL2/SDL2_rotozoom.h>
#include<SDL2_image/SDL_image.h>
#include "../primitives/Point.h"
#include "../essential/constants.h"
#include "../essential/random.h"
#include "PixelMod.h"
typedef uint8 uint8_t;
typedef uint32 uint32_t;

class Texture {
	protected:
		int xpos, ypos;
		SDL_Texture* texture;
	public:
		Texture();
		~Texture();
		Texture& operator=(const Texture& that);
		Texture(const Texture& that);
		void free();
		SDL_Surface* scaleToCoords(SDL_Surface* surf, float desiredWidth, float desiredHeight);
		void setAlpha(uint8 alpha);
		void setBlend(SDL_BlendMode mode);
		void setColorMod(uint8 red, uint8 green, uint8 blue);
		void setColorKey(uint8 red, uint8 green, uint8 blue);
		void draw(int x, int y, SDL_Renderer* renderer, SDL_Rect* clip = NULL, double angle = 0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
		void draw(SDL_Renderer* renderer, SDL_Rect* clip = NULL, double angle = 0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
		void draw(SDL_Renderer* renderer, Point offset);
		void drawAt(SDL_Renderer* renderer, Point position, Point offset);
		bool isLoaded();
		bool notLoaded();
		void createBlank(SDL_Renderer* renderer, int w, int h, uint32_t color = 0x0000000FF);
		SDL_Texture* getTexture();
		void setPos(int x = 0, int y = 0);
		void setPos(Point point);
		void loadFromFile(std::string path, SDL_Renderer* renderer, int xSize = 0, int ySize = 0);
		void normalizeTexture(SDL_Renderer* renderer);
		//TODO: Add more functionality
		// Filters
		void bilateralFilter(float valI, float valS, int kernelSize = 5);
		void dither();
		void testFilter();
		void floatyEdges();
};
