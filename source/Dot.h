#pragma once
#include "essential/constants.h"
#include "essential/MegaBase.h"
#include "game_entities/base/EntityBase.h"
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
		Point lastDelta;
		Timer tmp, pf;
	public:
		Dot(Point startingCoordinate);
		~Dot();
		bool doesLineCollide(const Line& ray) const override;
		bool overlap(const Rect& other) const override;
		bool overlap(const std::shared_ptr<ThingBase>& other) const override;
		float getAngle();
		float calcAngle(Point point);
		Line getRay();
		Point collideLine(const Line& ray) const override;
		Point getCenter();
		Point getPosition() const override;
		Rect getRect() const override;
		void collideTest();
		void draw(SDL_Renderer* renderer, Point offset = Point(0, 0)) override;
		void move(Point delta);
		void rayCast();
		void update() override;
		void velocityDelta(PointDelta acceleration);
};

int tempF(double val);
Rect tempF(Rect rect);
Point tempF(Point point);
