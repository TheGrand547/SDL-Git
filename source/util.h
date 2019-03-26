#pragma once
#include "Point.cpp"
#include<SDL2/SDL2_gfxPrimitives.h>
//Basic wrapper for parts of sdl2_gfx so I don't have to do work
void rectangleRGBA(SDL_Renderer *renderer, Point pointA, Point pointB, 
					uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	rectangleRGBA(renderer, pointA.x()-1, pointA.y()-1, pointB.x(), pointB.y(), 
					r, g, b, a);
}

void aalineRGBA(SDL_Renderer *renderer, Point *pointA, Point *pointB, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	aalineRGBA(renderer, pointA->x(), pointA->y(), pointB->x(), pointB->y(), r, g, b, a);
}

void boxRGBA(SDL_Renderer *renderer, Point pointA, Point pointB, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	boxRGBA(renderer, pointA.x()-1, pointA.y()-1, pointB.x()-1, pointB.y()-1, r, g, b, a);
}
	
