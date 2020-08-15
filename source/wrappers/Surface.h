#pragma once
#ifndef SURFACE_H
#define SURFACE_H
#include<string>
#include<SDL.h>
#include<SDL2_rotozoom.h>
#include "../essential/SDL_Headers.h"
#include "../primitives/Rect.h"
#include "Texture.h"

class Surface {
	private:
		// Methods there is no reason anyone outside should need to call
		SDL_Surface* createSurface(const int& width, const int& height) const;
	protected:
		bool changed, locked;
		SDL_Surface* surface;
		Texture internal;
		
	public:
		// TODO: Rearrange
		Surface();
		Surface(const Surface& surface);
		Surface(Surface&& surface);
		Surface(SDL_Surface*& surface);
		Surface(SDL_Surface*&& surface);
		~Surface();
		
		Surface& operator=(SDL_Surface*&& surface);
		Surface& operator=(Surface&& surface);
		Surface& operator=(SDL_Surface*& surface);
		Surface& operator=(const Surface& surface);
		
		int blitTo(Surface& surface, const Rect& srcRect = Rect(), const Rect& dstRect = Rect()) const;
		int setAlpha(const Uint8& alpha);
		int setBlend(const SDL_BlendMode& blend);
		int setBlend(const BLEND_MODE& blend);
		void setColorKey(const Uint32& color);
		void setColorKey(const SDL_Color& color);
		
		int height() const;
		int width() const;
		
		void draw(SDL_Renderer* renderer, Point position);
		void load(const std::string& path);
		void free();
		void scale(const double& width, const double& height, bool smooth = true);
		
		void finalize(SDL_Renderer* renderer); // Fully hardware accelerate the surface, making it completely a texture
		
		// Filters
		void bilateralFilter(const double valI, const double valS, const int kernelSize = 5, 
		        int xStart = -1, int yStart = -1, int width = 0, int height = 0);
		void dither();
		void floatyEdges();
		void limitPalette();
		void testFilter();
		
};
#endif
