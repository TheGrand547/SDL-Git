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
		int width, height;
		SDL_Renderer* renderer;
		SDL_Texture* texture;
		
		SDL_Texture* getBlankRenderTarget(SDL_Renderer* renderer);
	public:
		Texture();
		~Texture();
		Texture(const Texture& that);
		Texture(Texture&& that);
		Texture& operator=(Texture& that);
		Texture& operator=(Texture&& that);
		int getHeight() const;
		int getWidth() const;
		void free();
		void setAlpha(Uint8 alpha);
		void setBlend(SDL_BlendMode mode);
		void setColorMod(Uint8 red, Uint8 green, Uint8 blue);
		void setColorKey(Uint8 red, Uint8 green, Uint8 blue);
		// TODO: Add drawing to a rectangle, with a given size
		void draw(SDL_Renderer* renderer, Point position, SDL_COPY_EX_ARGS_DEFAULTS);
		bool isLoaded();
		bool notLoaded();
		void createBlank(SDL_Renderer* renderer, int w, int h, Uint32 color = 0x0000000FF);
		SDL_Texture* getRawTexture();
		
		void loadFromFile(SDL_Renderer* renderer, std::string path, int xSize = 0, int ySize = 0);
		void normalizeTexture(SDL_Renderer* renderer);
		
		// TODO: Add more static methods
		static Texture load(SDL_Renderer* renderer, std::string path);
		static Texture scaleTextureBy(SDL_Renderer* renderer, Texture texture, double xFactor, double yFactor);
		
		// TODO: Add more Filters
		// Filters
		void bilateralFilter(const float valI, const float valS, const int kernelSize = 5, 
		        const int xStart = 2, const int yStart = 2, int width = 0, int height = 0);
		void dither();
		void testFilter();
		void floatyEdges();
};
