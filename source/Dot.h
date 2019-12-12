#pragma once
#include<SDL2/SDL.h>
#include "primitives/Point.h"
#include "primitives/Rect.h"
#include "primitives/Vector.h"
#include "primitives/PointDelta.h"
#include "game_entities/CollideBaseGroup.h"
#include "game_entities/base/EntityBase.h"
#include "essential/constants.h"
#include "essential/MegaBase.h"
#include "wrappers/FpsText.h"
#include<math.h>

class Dot : public EntityBase, public MyBase { // Might not need MyBase
	private:
		BoundedPoint position;
		CollideBaseGroup* collision;
		Point lastDelta;
	public:
		Dot(Point startingCoordinate);
		~Dot();
		Point getCenter();
		float calcAngle(Point point);
		Point getPos();
		Rect getRect();
		Line getRay();
		float getAngle();
		void move(Point delta);
		void update(PointDelta acceleration);
		void draw();
		void collideTest();
		void rayCast();
		
		void setCollision(CollideBaseGroup& boxes);
};

int tempF(double val);
Rect tempF(Rect rect);
Point tempF(Point point);
