#pragma once
#ifndef SDL_HEADERS_HELP_H
#define SDL_HEADERS_HELP_H
#include<SDL.h>
#include<SDL2_framerate.h>
#include<SDL2_gfxPrimitives.h>
#include<SDL2_rotozoom.h>
#include<SDL_thread.h>
#include<SDL_image.h>
#include<SDL_ttf.h>

typedef uint8_t  Uint8;
typedef uint32_t Uint32;

// It might look stupid but I promise it is NOT
#define SURFACE_FLAGS 0

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

/*
struct Color : SDL_Color {
	Color(Uint32 color) {
		this->r = (color & RMASK) >> RSHIFT;
		this->g = (color & RMASK) >> RSHIFT;
		this->b = (color & RMASK) >> RSHIFT;
		this->a = (color & RMASK) >> RSHIFT;
	}
};*/


// Two macros for arguments that are unlikely to be used in rendering, but should be there for extra functionality
// Macros to make code more readable
#define SDL_COPY_EX_ARGS_DEFAULTS SDL_Rect* clip = NULL, double angle = 0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE
#define SDL_COPY_EX_ARGS_PASS clip, angle, center, flip
#define SDL_COPY_EX_ARGS SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip

// TODO: Maybe write a wrapper thingy for all of sdl things, like a SDL namespace with texture as a base class?
#endif
