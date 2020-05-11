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
		void draw(SDL_Renderer* renderer, Point position, SDL_COPY_EX_ARGS_DEFAULTS);
		bool isLoaded();
		bool notLoaded();
		void createBlank(SDL_Renderer* renderer, int w, int h, Uint32 color = 0x0000000FF);
		SDL_Texture* getRawTexture();
		
		void loadFromFile(SDL_Renderer* renderer, std::string path, int xSize = 0, int ySize = 0);
		void normalizeTexture(SDL_Renderer* renderer);
		
		static Texture load(SDL_Renderer* renderer, std::string path);
		static Texture scaleTextureBy(SDL_Renderer* renderer, Texture texture, double xFactor, double yFactor);
		//TODO: Add more functionality
		// Filters
		void bilateralFilter(const float valI, const float valS, const int kernelSize = 5, 
		        const int xStart = 2, const int yStart = 2, int width = 0, int height = 0);
		void dither();
		void testFilter();
		void floatyEdges();
};
