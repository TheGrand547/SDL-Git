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
		std::vector<CollideBase*> group;
	public:
		CollideBaseGroup();
		~CollideBaseGroup();
		CollideBase* operator[](int index);
		int size();
		void drawGroup();
		void drawGroup(BoundedPoint& offset) {}
		void push_back(CollideBase* collision);
};

bool collideRect(Rect rect, CollideBaseGroup* boxes);
Point smallestDistanceFrom(CollideBaseGroup* boxes, Point origin, Line ray);
Point collideTestVectorToRay(CollideBaseGroup* boxes, Line ray);
bool collideRectTest(Rect rect, CollideBaseGroup* vec);
#endif
