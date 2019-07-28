#pragma once
#include<SDL2/SDL.h>
#include "primitives/Point.h"
#include "primitives/Rect.h"
#include "primitives/PointDelta.h"
#include "game_entities/CollideBaseGroup.h"
#include "essential/constants.h"
#include "essential/MegaBase.h"
#include<math.h>

class Dot: public MyBase {
	private:
		float angle;
		BoundedPoint position;
	public:
		Dot(Point startingCoordinate);
		~Dot();
		Point getCenter();
		void evalAngle(Point delta);
		float calcAngle(Point point);
		void operator+=(Point delta);
		void operator-=(Point delta);
		Point getPos();
		Rect getRect();
		Line getRay();
		float getAngle();
		void draw();
		void collideTest(PointDelta delta, CollideBaseGroup& boxes);
		void rayCast(CollideBaseGroup& boxes);
};
