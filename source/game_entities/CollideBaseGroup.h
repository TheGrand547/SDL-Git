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
		CollideBase*& operator[](int index);
		bool exists() override;
		int size() override;
		void clearGroup() override;
		void drawGroup() override;
		void drawGroup(BoundedPoint& offset) {}
		void push_back(CollideBase* collision);
};

bool checkCollisionBetweenLineAndGroup(CollideBaseGroup& group, Line ray);
bool checkCollisionBetweenLineAndGroup(CollideBaseGroup* group, Line ray);
bool collideRect(CollideBaseGroup& boxes, Rect rect);
bool collideRect(CollideBaseGroup* boxes, Rect rect);
bool collideRectTest(CollideBaseGroup& vec, Rect rect);
bool collideRectTest(CollideBaseGroup* vec, Rect rect);
Point collideTestVectorToRay(CollideBaseGroup& boxes, Line ray);
Point collideTestVectorToRay(CollideBaseGroup* boxes, Line ray);
Point smallestDistanceFrom(CollideBaseGroup& boxes, Point origin, Line ray);
Point smallestDistanceFrom(CollideBaseGroup* boxes, Point origin, Line ray);
#endif
