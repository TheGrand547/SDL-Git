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


#define SURFACE_FLAGS 0
enum BLEND_MODE {
	NONE = SDL_BLENDMODE_NONE,
	BLEND = SDL_BLENDMODE_BLEND,
	ADD = SDL_BLENDMODE_ADD,
	MOD = SDL_BLENDMODE_MOD
};

enum COLOR_MASK {
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    RMASK = 0xff000000,
	GMASK = 0x00ff0000,
    BBASK = 0x0000ff00,
    amask = 0x000000ff
#else
    RMASK = 0x000000ff,
    GMASK = 0x0000ff00,
    BMASK = 0x00ff0000,
    AMASK = 0xff000000
#endif
};



// Two macros for arguments that are unlikely to be used in rendering, but should be there for extra functionality
// Macros to make code more readable
#define SDL_COPY_EX_ARGS_DEFAULTS SDL_Rect* clip = NULL, double angle = 0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE
#define SDL_COPY_EX_ARGS_PASS clip, angle, center, flip
#define SDL_COPY_EX_ARGS SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip

// TODO: Maybe write a wrapper thingy for all of sdl things, like a SDL namespace with texture as a base class?
#endif
