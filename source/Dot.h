#pragma once
#include<SDL2/SDL.h>
#include "primitives/Point.h"
#include "primitives/Rect.h"
#include "primitives/Vector.h"
#include "primitives/PointDelta.h"
#include "game_entities/CollideBaseGroup.h"
#include "essential/constants.h"
#include "essential/MegaBase.h"
#include "wrappers/FpsText.h"
#include<math.h>

class Dot : public MyBase {
	private:
		float angle;
		BoundedPoint position;
		PointDelta velocity;
		Point acceleration;
		CollideBaseGroup* collision;
		FpsText* f;
	public:
		Dot(Point startingCoordinate);
		~Dot();
		Point getCenter();
		void evalAngle(Point delta);
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
		void setTimer(FpsText& f);
};
