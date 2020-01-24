#pragma once
#include "essential/constants.h"
#include "essential/MegaBase.h"
#include "game_entities/base/EntityBase.h"
#include "game_entities/CollideBaseGroup.h"
#include "primitives/Point.h"
#include "primitives/PointDelta.h"
#include "primitives/Rect.h"
#include "primitives/Vector.h"
#include "wrappers/FpsText.h"
#include<math.h>
#include<memory>
#include<SDL2/SDL.h>

class Dot : public EntityBase, public MyBase { 
	private:
		BoundedPoint position;
		CollideBaseGroup* collision;
		Point lastDelta;
	public:
		Dot(Point startingCoordinate);
		~Dot();
		bool overlap(Rect other) override;
		bool overlap(std::shared_ptr<ThingBase>& other) override;
		float getAngle();
		float calcAngle(Point point);
		Line getRay();
		Point getCenter();
		Point getPos();
		Rect getRect() const override;
		void collideTest();
		void draw();
		void move(Point delta);
		void rayCast();
		void setCollision(CollideBaseGroup& boxes);
		void update(PointDelta acceleration);
};

int tempF(double val);
Rect tempF(Rect rect);
Point tempF(Point point);
