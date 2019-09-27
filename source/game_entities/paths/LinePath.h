#pragma once
#include "Path.h"
#include "../../primitives/Point.h"
#include "../../essential/random.h"

class LinePath : public Path {
	private:
		Point delta;
		int maxTicks;
	public:
		LinePath();
		LinePath(Point vector, float tickTime, int repeatCount = Path::SINGLE_LOOP);
		~LinePath();
		LinePath(Point startingPos, Point endingPos, float tickTime, int repeatCount = Path::SINGLE_LOOP);
		void stop();
		bool isFinished();
		void modify(float time);
};
