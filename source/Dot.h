#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include "game_entities/base/EntityBase.h"
#include "primitives/Point.h"
#include "primitives/Rect.h"
#include "wrappers/FpsText.h"
#include "wrappers/MovementWrapper.h"
#include "wrappers/Surface.h"
#include "BoundedPoint.h"
#include "Color.h"
#include <math.h>
#include <memory>
#include <SDL.h>

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
		// TODO: Remove duplicates of this and such
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
};
#endif
