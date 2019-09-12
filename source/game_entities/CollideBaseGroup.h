#pragma once
#ifndef COLLIDE_BASE_DRAW_GROUP_H
#define COLLIDE_BASE_DRAW_GROUP_H
#include<memory>
#include<SDL2/SDL.h>
#include<vector>
#include "DrawGroup.h"
#include "base/CollideBase.h"
#include "../BoundedPoint.h"
#include "../wrappers/SuperTexture.h"
class CollideBaseGroup : public DrawGroup {
	private:
		std::vector<CollideBase*> group;
		SDL_Renderer* renderer;
		BoundedPoint* offset;
	public:
		CollideBaseGroup(SDL_Renderer* renderer, BoundedPoint& offset);
		~CollideBaseGroup();
		CollideBase*& operator[](int index);
		bool exists() override;
		int size() override;
		void clearGroup() override;
		void drawGroup() override;
		void push_back(CollideBase* collision);
		/* CollisionGroup Specific Commands */
		bool doesCollideWith(Rect rect);
		bool doesCollideWith(Line ray);
		bool doesNotCollideWith(Rect rect);
		bool doesNotCollideWith(Line line);
		bool doesPlayerNotCollide(Rect rect);
		Point closestPointThatCollidesWith(Line ray);
};
#endif
