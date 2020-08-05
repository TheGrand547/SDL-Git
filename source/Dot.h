#pragma once
#include "PositionLock.h"
#include "essential/constants.h"
#include "essential/util.h"
#include "game_entities/base/EntityBase.h"
#include "primitives/Point.h"
#include "primitives/Rect.h"
#include "primitives/Vector.h"
#include "wrappers/FpsText.h"
#include "wrappers/MovementWrapper.h"
#include<math.h>
#include<memory>
#include<SDL2/SDL.h>

class Dot : public EntityBase, public MyBase { 
	private:
		BoundedPoint position;
		MovementWrapper mvmt; // >:(
		Point lastDelta;
	public:
		Dot(Point startingCoordinate);
		~Dot();
		bool doesLineCollide(const Line& ray) const override;
		bool overlap(const Polygon& other) const override;
		bool overlap(const std::shared_ptr<ThingBase>& other) const override;
		bool wideOverlap(const Polygon& other) const override;
		double calcAngle(Point point);
		double getAngle();
		Line getRay();
		Point collideLine(const Line& ray) const override;
		Point getCenter();
		Point getPosition() const override;
		Rect getBoundingRect() const override;
		void collideTest();
		void draw(SDL_Renderer* renderer, Point offset = Point(0, 0)) override;
		void rayCast();
		void update() override;
		void velocityDelta(Point acceleration);
};
