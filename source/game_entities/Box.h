#pragma once
#include<iostream>
#include<SDL2/SDL.h>
#include<vector>
#include "../essential/constants.h"
#include "../primitives/Point.h"
#include "../primitives/Rect.h"
#include "../wrappers/SuperTexture.h"	
#include "../wrappers/Texture.h"
#include "../BoundedPoint.h"
#include "../essential/util.h"
#include "base/CollideBase.h"
#include "CollideBaseGroup.h"

typedef Uint32 uint32_t;
class Box : public CollideBase{
	private:
		Rect myRect;
		SuperTexture* mTexture;
	public:
		Box();
		Box(Point position);
		~Box();
		Box(const Box& that);
		Box &operator=(const Box& that);
		void draw(SDL_Renderer* renderer, Point offset = Point(0, 0));
		Point collideLine(Line& ray);
		bool overlap(Rect& other);
		void setTexture(SuperTexture* texture);
		static SuperTexture* createBoxTexture(SDL_Renderer* renderer);
		static void setTexture(std::vector<Box*>* vec, SuperTexture* texture);
};
