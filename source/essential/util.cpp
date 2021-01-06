#include "util.h"
#include "SDL_Headers.h"

void rectangleRGBA(SDL_Renderer *renderer, Point pointA, Point pointB, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	rectangleRGBA(renderer, pointA.x, pointA.y, pointB.x, pointB.y, r, g, b, a);
}

void aalineRGBA(SDL_Renderer* renderer, Point pointA, Point pointB, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	aalineRGBA(renderer, pointA.x, pointA.y, pointB.x, pointB.y, r, g, b, a);
}

void lineRGBA(SDL_Renderer* renderer, Point pointA, Point pointB, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	lineRGBA(renderer, pointA.x, pointA.y, pointB.x, pointB.y, r, g, b, a);
}

void boxRGBA(SDL_Renderer *renderer, Point pointA, Point pointB, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	boxRGBA(renderer, pointA.x, pointA.y, pointB.x - 1, pointB.y - 1, r, g, b, a);
}

void setRenderColors(SDL_Renderer* renderer, SDL_Color rect) {
	SDL_SetRenderDrawColor(renderer, rect.r, rect.g, rect.b, rect.a);
}

int keyCodeFromEvent(SDL_Event event) {
	return event.key.keysym.sym;
}

void orderPoints(Point& pointA, Point& pointB) {
	if (pointB.distanceToPoint() < pointA.distanceToPoint()) {
		Point temp = pointA;
		pointA = pointB;
		pointB = temp;
	}
}

void createDetatchedThread(int(*method)(void*), void* arg, const char* name) {
	SDL_Thread* newThread = SDL_CreateThread(method, name, arg);
	SDL_DetachThread(newThread);
}

// TEMP TEMP TEMP TEMP TEMP
int threadTest(void* ptr) {
	int* pter = static_cast<int*>(ptr);
	pter++;
	for (int i = 0; i < 10; i++) {
		SDL_Delay(250);
		std::cout << "It's been " << i * 250 << " ms since i started." << std::endl;
	} 
	std::cout << "I died :(" << std::endl;
	return 0;
}
