#pragma once
#ifndef ZERO_RADIUS_TURN_PATH_H
#define ZERO_RADIUS_TURN_PATH_H
#include "Path.h"

class ZeroRadiusTurnPath : public Path {
	private:
		bool clockwise;
		double maxTicks, startingAngle, targetAngle;
	public:
		ZeroRadiusTurnPath(double targetAngle, double time, bool clockwise = false);
		~ZeroRadiusTurnPath();
		bool isFinished() const override;
		void modify(double delta) override;
		void start() override;
		void stop() override;
};
#endif
