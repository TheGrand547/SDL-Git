#pragma once
#ifndef BIG_WALL_H
#define BILL_WALL_H
#include "../primitives/Point.h"
#include "../primitives/Polygon.h"
#include "../primitives/Rect.h"
#include "base/ThingBase.h"
#include<memory>
#include<SDL2/SDL.h>

class BigWall : public ThingBase {
	protected:
		Rect rect;
	public:
		BigWall(Rect rect);
		~BigWall();
		bool doesLineCollide(const Line& ray) const override;
		bool overlap(const Polygon& other) const override;
		bool overlap(const std::shared_ptr<ThingBase>& other) const override;
		double originDistance() const override;
		Point collideLine(const Line& ray) const override;
		Point getPosition() const override;
		Rect getBoundingRect() const override;
		void draw() override;
};
#endif
