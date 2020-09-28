#pragma once
#include "Color.h"
#include "PositionLock.h"
#include "essential/constants.h"
#include "essential/util.h"
#include "game_entities/base/EntityBase.h"
#include "primitives/Point.h"
#include "primitives/Rect.h"
#include "primitives/Vector.h"
#include "wrappers/FpsText.h"
#include "wrappers/MovementWrapper.h"
#include "wrappers/Surface.h"
#include <math.h>
#include <memory>
#include <SDL2/SDL.h>

class Dot : public EntityBase, public Color { 
	private:
		BoundedPoint position;
		MovementWrapper mvmt; // >:(
		Point lastDelta;
		
		Surface surface;
	public:
		Dot(Point startingCoordinate);
		~Dot();
		bool doesLineCollide(const Line& ray) const override;
		bool overlap(const Polygon& other) const override;
		bool overlap(const std::shared_ptr<ThingBase>& other) const override;
		double calcAngle(Point point);
		double getAngle();
		Line getRay();
		Point collideLine(const Line& ray) const override;
		Point getCenter();
		Point getPosition() const override;
		Rect getBoundingRect() const override;
		void collideTest();
		void draw() override;
		void rayCast();
		void shoot();
		void update() override;
		void velocityDelta(Point acceleration);
};
