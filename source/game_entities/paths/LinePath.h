#pragma once
#include "Path.h"
#include "../../primitives/Point.h"
#include "../../essential/random.h"

class LinePath : public Path {
	private:
		PointDelta delta;
		int maxTicks;
		Point begin;
	public:
		LinePath();
		LinePath(PointDelta vector, float distance, int repeatCount = Path::SINGLE_LOOP);
		~LinePath();
		void start();
		void stop();
		bool isFinished() const;
		void modify(float time);
};
