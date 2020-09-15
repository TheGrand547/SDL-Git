#pragma once
#ifndef BASIC_BULLET_H
#define BASIC_BULLET_H
#include "base/ThingBase.h"
#include "../wrappers/MovementWrapper.h"

class BasicBullet : public ThingBase {
	protected:
		MovementWrapper mvmt;
		Point delta;
	public:
		BasicBullet(double angle, double speed);
		BasicBullet(Point delta);
		~BasicBullet();
		bool doesLineCollide(const Line& ray) const override;
		bool overlap(const Polygon& other) const override;
		bool overlap(const ThingPtr& other) const override;
		double originDistance() const override;
		Point getPosition() const override;
		Point collideLine(const Line& ray) const override;
		Rect getBoundingRect() const override;
		void draw() override;
		void update() override;
};
#endif
