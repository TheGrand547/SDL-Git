#pragma once
#ifndef BIG_WALL_H
#define BILL_WALL_H
#include "../primitives/Point.h"
#include "../primitives/Rect.h"
#include "base/ThingBase.h"
#include<memory>
#include<SDL2/SDL.h>

class BigWall : public ThingBase {
	private:
		Rect rect;
	public:
		BigWall(Rect rect);
		~BigWall();
		bool doesLineCollide(const Line& ray) const override;
		bool overlap(const Rect& other) const override;
		bool overlap(const std::shared_ptr<ThingBase>& other) const override;
		double originDistance() const override;
		Point collideLine(const Line& ray) const override;
		Point getPosition() const override;
		Rect getRect() const override;
		void addNodes() override;
		void draw(SDL_Renderer* renderer, Point offset = Point(0, 0)) override;
		void gimme(std::vector<Point>& vec) const override;
};
#endif
