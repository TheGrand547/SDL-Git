#pragma once
#include "../primitives/Point.h"
#include "../Color.h"
#include <SDL.h>
#include <SDL_thread.h>
#include <SDL2_gfxPrimitives.h>

#define M_PI_8 (M_PI_4 / 2)

//Basic wrapper for parts of sdl2_gfx so I don't have to do work
void rectangleRGBA(SDL_Renderer* renderer, Point pointA, Point pointB, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
void aalineRGBA(SDL_Renderer* renderer, Point pointA, Point pointB, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
void boxRGBA(SDL_Renderer* renderer, Point pointA, Point pointB, uint8_t r, uint8_t g, uint8_t b, uint8_t a);

void setRenderColors(SDL_Renderer* renderer, SDL_Color rect);

void orderPoints(Point& pointA, Point& pointB);

int keyCodeFromEvent(SDL_Event event);

// TEMP TEMP TEMP TEMP TEMP
void createDetatchedThread(int(*method)(void*), void* arg = NULL, const char* name = "new thread");

int threadTest(void* ptr);
