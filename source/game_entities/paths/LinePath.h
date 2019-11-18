#pragma once
#include "Path.h"
#include "../../primitives/Point.h"
#include "../../essential/random.h"

class LinePath : public Path {
	private:
		PointDelta delta;
		int maxTicks;
	public:
		LinePath();
		LinePath(PointDelta vector, float distance, int repeatCount = Path::SINGLE_LOOP);
		~LinePath();
		void stop();
		bool isFinished();
		void modify(float time);
};
