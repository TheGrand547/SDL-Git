#pragma once
#ifndef FOOT_STEPS_H
#define FOOT_STEPS_H
#include "base/ThingBase.h"
#include "../wrappers/Timer.h"
#include<queue>


class FootSteps : public ThingBase {
	protected:
		std::queue<Point> storage;
	public:
		FootSteps();
		~FootSteps();
		bool overlap(const Polygon& other) const override
		bool overlap(const std::shared_ptr<ThingBase>& other) const override;
		
		double originDistance() const override;
		Point collideLine(const Line& ray) const override;
		Point getPosition() const override;
		Rect getBoundingRect() const override;
		void draw(SDL_Renderer* renderer, Point offset = Point(0, 0)) override;
		void update() override; // Add a new foot step if the player has moved and it's been a certain amount of time
		
};
#endif
