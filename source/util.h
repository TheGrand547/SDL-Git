#pragma once
#include "Point.cpp"

void rectangleRGBA(SDL_Renderer *renderer, Point pointA, Point pointB, 
					uint8_t r, uint8_t g, uint8_t b, uint8_t a);
void aalineRGBA(SDL_Renderer *renderer, Point *pointA, Point *pointB, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
void boxRGBA(SDL_Renderer *renderer, Point pointA, Point pointB, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
void mMax(int numA, int numB, int &iMin, int &iMax);
void mMax(int numA, int numB, float &iMin, float &iMax);
bool valueInRange(int value, int min, int max);
bool valueInRange(float value, float min, float max);
bool valueInRange(float value, float *min, float *max);
bool lValueInRange(float value, float min, float max);
bool lValueInRange(float value, float *min, float *max);

#include "Rect.h"
#include "Box.h"
#include "Line.h"
#include<vector>
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


bool collideRect(Rect rect, std::vector<Box> &vec) {
	bool result = false;
	for (int i = 0; i < (&vec)->size(); i++) {
		result = result || ((&vec[i])->overlap(rect));
	}
	return result;
}

void mMax(int numA, int numB, int &iMin, int &iMax) {
	if (numA >= numB) {
		iMin = numB;
		iMax = numA;
	} else {
		iMin = numA;
		iMax = numB;
	}
}
void mMax(int numA, int numB, float &iMin, float &iMax) {
	if (numA >= numB) {
		iMin = numB;
		iMax = numA;
	} else {
		iMin = numA;
		iMax = numB;
	}
}

bool valueInRange(int value, int min, int max){ 
	return (value >= min) && (value <= max); 
}

bool valueInRange(float value, float min, float max){ 
	return (value >= min) && (value <= max); 
}

bool valueInRange(float value, float *min, float *max){ 
	return (value >= *min) && (value < *max); 
}

bool lValueInRange(float value, float min, float max){ 
	return ((value >= min) && (value <= max)); 
}
bool lValueInRange(float value, float *min, float *max){ 
	return ((value >= *min) && (value <= *max)); 
}

Point smallestDistanceFrom(std::vector<Box> &boxes, Point origin, Line ray) {
	Point stored;
	for (int i = 0; i < (&boxes)->size(); i++) {
		stored = smallerDistance(origin, (&boxes[i])->collideLine(ray), stored);
	}
	return stored;
}

Point collideTestVectorToRay(std::vector<Box> &boxes, Line ray) {
	return smallestDistanceFrom(boxes, ray.getOrigin(), ray);
}
