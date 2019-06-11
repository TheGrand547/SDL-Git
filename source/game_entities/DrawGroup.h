#pragma once
#ifndef DRAW_GROUP_H
#define DRAW_GROUP_H
#include<SDL2/SDL.h>
#include "../BoundedPoint.h"
#include "../essential/MegaBase.h"
class DrawGroup {
	public:
		DrawGroup() {}
		virtual ~DrawGroup() {}
		virtual void drawGroup() = 0;
};
#endif
