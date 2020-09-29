#pragma once
#ifndef SDL_HEADERS_HELP_H
#define SDL_HEADERS_HELP_H
#include "../primitives/Point.h"
#include "typedefs.h"
#include <SDL.h>
#include <SDL2_framerate.h>
#include <SDL2_gfxPrimitives.h>
#include <SDL2_rotozoom.h>
#include <SDL_thread.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

// Package rendering conext and the relevant offset in one tidy package
struct Renderer {
	Point offset = Point(0, 0);
	SDL_Renderer* renderer = NULL;
	Renderer operator+(const Point& point) const;
	Renderer operator-(const Point& point) const;
	void operator+=(const Point& point);
	void operator-=(const Point& point);
};
Renderer operator+(const Point& point, const Renderer& renderer);
Renderer operator-(const Point& point, const Renderer& renderer);

// It might look stupid but I promise it is NOT
#define SURFACE_FLAGS 0
#define PIXEL_DEPTH  32

enum BLEND_MODE {
	NONE  = SDL_BLENDMODE_NONE,
	BLEND = SDL_BLENDMODE_BLEND,
	ADD   = SDL_BLENDMODE_ADD,
	MOD   = SDL_BLENDMODE_MOD
};

enum COLOR_MASK : Uint32 {
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    RMASK = 0xFF000000,
	GMASK = 0x00FF0000,
    BMASK = 0x0000FF00,
    AMASK = 0x000000FF
    
    RSHIFT = 24,
    GSHIFT = 16,
    BSHIFT = 8,
    ASHIFT = 0
#else
    RMASK = 0x000000FF,
    GMASK = 0x0000FF00,
    BMASK = 0x00FF0000,
    AMASK = 0xFF000000,
    
    RSHIFT = 0,
    GSHIFT = 8,
    BSHIFT = 16,
    ASHIFT = 24
#endif
};

// Two macros for arguments that are unlikely to be used in rendering, but should be there for extra functionality
// Macros to make code more readable
#define SDL_COPY_EX_ARGS_DEFAULTS SDL_Rect* clip = NULL, double angle = 0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE
#define SDL_COPY_EX_ARGS_PASS clip, angle, center, flip
#define SDL_COPY_EX_ARGS SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip

// TODO: Maybe write a wrapper thingy for all of sdl things, like a SDL namespace with texture as a base class?
#endif
