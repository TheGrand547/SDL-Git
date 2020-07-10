#include<SDL.h>
#include<SDL2_framerate.h>
#include<SDL2_gfxPrimitives.h>
#include<SDL2_rotozoom.h>
#include<SDL_thread.h>
#include<SDL_image.h>
#include<SDL_ttf.h>

// Two macros for arguments that are unlikely to be used in rendering, but should be there for extra functionality
// Macros to make code more readable
#define SDL_COPY_EX_ARGS_DEFAULTS SDL_Rect* clip = NULL, double angle = 0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE
#define SDL_COPY_EX_ARGS SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip
