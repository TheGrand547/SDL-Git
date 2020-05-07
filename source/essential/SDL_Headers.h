#ifdef __APPLE__
#include<SDL2/SDL.h>
#include<SDL2/SDL2_framerate.h>
#include<SDL2/SDL2_gfxPrimitives.h>
#include<SDL2/SDL2_rotozoom.h>
#include<SDL2/SDL_thread.h>
#include<SDL2_image/SDL_image.h>
#include<SDL2_ttf/SDL_ttf.h>
#endif

#ifdef __LINUX__
#include<SDL2/SDL2.h>
#include<SDL2/SDL2_framerate.h>
#include<SDL2/SDL2_gfxPrimitives.h>
#include<SDL2/SDL2_rotozoom.h>
#include<SDL2/SDL_thread.h>
#include<SDL2/SDL_image.h>
#include<SDL2_ttf/SDL_ttf.h>
#endif

// Two macros for arguments that are unlikely to be used in rendering, but should be there for excess functionality
// Macros to make code more readable
#define SDL_COPY_EX_ARGS_DEFAULTS SDL_Rect* clip = NULL, double angle = 0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE
#define SDL_COPY_EX_ARGS SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip
