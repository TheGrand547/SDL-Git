#pragma once
#ifndef ZERO_RADIUS_TURN_PATH_H
#define ZERO_RADIUS_TURN_PATH_H
#include "Path.h"

class ZeroRadiusTurnPath : public Path {
	private:
		float startingAngle, targetAngle, maxTicks;
		bool clockwise;
	public:
		ZeroRadiusTurnPath(float targetAngle, float time, bool clockwise = false);
		~ZeroRadiusTurnPath();
		bool isFinished() const override;
		void start() override;
		void stop() override;
		void modify(float delta) override;
};
#endif
