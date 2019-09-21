#pragma once
#include<SDL2/SDL.h>
#include<SDL2/SDL_thread.h>
#include<SDL2/SDL2_gfxPrimitives.h>
#include "../primitives/Point.h"
#include "../MyBase.h"

//Basic wrapper for parts of sdl2_gfx so I don't have to do work
inline void rectangleRGBA(SDL_Renderer *renderer, Point pointA, Point pointB, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	rectangleRGBA(renderer, pointA.x(), pointA.y(), pointB.x(), pointB.y(), r, g, b, a);
}

inline void aalineRGBA(SDL_Renderer* renderer, Point pointA, Point pointB, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	aalineRGBA(renderer, pointA.x(), pointA.y(), pointB.x(), pointB.y(), r, g, b, a);
}

inline void aalineRGBA(SDL_Renderer *renderer, Point *pointA, Point *pointB, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	aalineRGBA(renderer, *pointA, *pointA, r, g, b, a);
}

inline void aalineRGBA(SDL_Renderer *renderer, Point *pointA, Point *pointB, uint8_t r, uint8_t g, uint8_t b, uint8_t a, Point offset) {
	/* So MaNy BeAuTiFuL pOiNtErS */
	aalineRGBA(renderer, pointA->x() - offset.x(), pointA->y() - offset.y(), pointB->x() - offset.x(), pointB->y() - offset.y(), r, g, b, a);
}

inline void boxRGBA(SDL_Renderer *renderer, Point pointA, Point pointB, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	boxRGBA(renderer, pointA.x(), pointA.y(), pointB.x() - 1, pointB.y() - 1, r, g, b, a);
}

inline void setRenderColors(SDL_Renderer* renderer, SDL_Color rect) {
	SDL_SetRenderDrawColor(renderer, rect.r, rect.g, rect.b, rect.a);
}

inline int keyCodeFromEvent(SDL_Event event) {
	return event.key.keysym.sym;
}

inline void createDetatchedThread(int(*method)(void*), void* arg = NULL, const char* name = "new thread") {
	SDL_Thread* newThread = SDL_CreateThread(method, name, arg);
	SDL_DetachThread(newThread);
}

// TEMP TEMP TEMP TEMP TEMP
inline int threadTest(void* ptr) {
	for (int i = 0; i < 10; i++) {
		SDL_Delay(250);
		std::cout << "It's been " << i * 250 << " ms since i started." << std::endl;
	} 
	std::cout << "I died :(" << std::endl;
	return 0;
}
