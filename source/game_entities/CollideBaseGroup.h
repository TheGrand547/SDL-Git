#pragma once
#ifndef COLLIDE_BASE_DRAW_GROUP_H
#define COLLIDE_BASE_DRAW_GROUP_H
#include<SDL2/SDL.h>
#include<vector>
#include "DrawGroup.h"
#include "base/CollideBase.h"
#include "../BoundedPoint.h"
#include "../wrappers/SuperTexture.h"
class CollideBaseGroup : public DrawGroup {
	private:
		std::vector<CollideBase*>* group;
	public:
		CollideBaseGroup();
		~CollideBaseGroup();
		CollideBase* operator[](int index);
		std::vector<CollideBase*>* get();
		int size();
		void drawGroup(SDL_Renderer* renderer, BoundedPoint& screenPosition);
		void push_back(CollideBase* collision);
		void setTexture(SuperTexture* texture);
};
#endif
