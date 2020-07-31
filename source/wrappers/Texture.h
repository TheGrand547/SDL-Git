#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H
#include<iostream>
#include<SDL.h>
#include<SDL2_rotozoom.h>
#include<SDL_image.h>
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
		Texture& operator=(SDL_Texture*& that);
		Texture& operator=(SDL_Texture*&& that);
		int getHeight() const;
		int getWidth() const;
		void free();
		void setAlpha(Uint8 alpha);
		void setBlend(SDL_BlendMode mode);
		void setColorMod(Uint8 red, Uint8 green, Uint8 blue);
		void setColorKey(Uint8 red, Uint8 green, Uint8 blue);
		void draw(SDL_Renderer* renderer, Point position, SDL_COPY_EX_ARGS_DEFAULTS);
		void draw(SDL_Renderer* renderer, const SDL_Rect& rect, SDL_COPY_EX_ARGS_DEFAULTS);
		void drawCentered(SDL_Renderer* renderer, Point position, SDL_COPY_EX_ARGS_DEFAULTS);
		bool isLoaded();
		bool notLoaded();
		void createBlank(SDL_Renderer* renderer, int w, int h, Uint32 color = 0x0000000FF);
		SDL_Texture*& getRawTexture(); // ONLY USE IF YOU KNOW WHAT YOU'RE DOING
		
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
		
		// TODO: Recreate SDL methods with Texture
		// Friends
		friend int SDL_GetTextureAlphaMod(Texture& texture, Uint8* blendMode);
		friend int SDL_GetTextureAlphaMod(Texture& texture, Uint8& blendMode);
		
		friend int SDL_GetTextureBlendMode(Texture& texture, SDL_BlendMode* blendMode);
		friend int SDL_GetTextureBlendMode(Texture& texture, SDL_BlendMode& blendMode);
		
		friend int SDL_GetTextureColorMod(Texture& texture, Uint8* r, Uint8* g, Uint8* b);
		friend int SDL_GetTextureColorMod(Texture& texture, Uint8& r, Uint8& g, Uint8& b);
		
		friend int SDL_LockTexture(Texture& texture, const SDL_Rect*& rect, void**& pixels, int*& pitch);
		friend int SDL_LockTexture(Texture& texture, const SDL_Rect& rect, void*& pixels, int& pitch);
		
		friend int SDL_QueryTexture(Texture& texture, Uint32*& format, int* access, int* w, int* h);
		friend int SDL_QueryTexture(Texture& texture, Uint32& format, int& access, int& w, int& h);
		
		friend int SDL_RenderCopy(SDL_Renderer* renderer, Texture& texture, const SDL_Rect* src, const SDL_Rect* dst);
		friend int SDL_RenderCopyEx(SDL_Renderer* renderer, Texture& texture, const SDL_Rect* src, const SDL_Rect* dst, const double& angle, const SDL_Point* center, const SDL_RendererFlip& flip);
		
		friend int SDL_SetRenderTarget(SDL_Renderer* renderer, Texture& texture);
		friend int SDL_SetTextureAlphaMod(Texture& texture, const Uint8& alpha);
		friend int SDL_SetTextureBlendMode(Texture& texture, SDL_BlendMode blendMode);
		friend int SDL_SetTextureColorMod(Texture& texture, const Uint8& r, const Uint8& g, const Uint8& b);
		friend int SDL_UpdateTexture(Texture& texture, const SDL_Rect*& rect, const void* pixels, int pitch);
		friend int SDL_UpdateTexture(Texture& texture, const SDL_Rect& rect, const void*& pixels, const int& pitch);
		friend void SDL_DestroyTexture(Texture& texture);
		friend void SDL_UnlockTexture(Texture& texture);
};
#endif
