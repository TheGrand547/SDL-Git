#pragma once
#ifndef LINE_PATH_H
#define LINE_PATH_H
#include "../../primitives/Point.h"
#include "Path.h"

class LinePath : public Path {
	private:
		int maxTicks;
		Point begin, delta;
	public:
		LinePath();
		LinePath(Point vector, double distance, int repeatCount = Path::SINGLE_LOOP);
		~LinePath();
		bool isFinished() const override;
		void modify(double time) override;
		void start() override;
		void stop() override;
};
#endif
