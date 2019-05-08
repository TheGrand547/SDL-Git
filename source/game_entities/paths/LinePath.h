#pragma once
#include "Path.h"
#include "../../primatives/Point.h"

class LinePath : public Path<Point> {
	private:
		Point delta;
		int maxTicks;
	public:
		LinePath() : Path<Point>(NULL) {
			this->delta = Point(0, 0);
			this->maxTicks = 1;
		}
		
		/* Tick time is the duration in milliseconds, which must be adjusted for the refresh rate of paths */
		
		LinePath(Point* target, Point startingPos, Point endingPos, int tickTime, int repeatCount = Path::SINGLE_LOOP) : Path<Point>(target) {
			this->delta = (endingPos - startingPos) / (tickTime / 10);
			if (repeatCount == Path::SINGLE_LOOP) {
				this->maxTicks = tickTime / 10;
			} else {
				this->maxTicks = repeatCount * tickTime / 10;
			}
		}
		
		bool isFinished() {
			if (this->ticksDone > this->maxTicks && this->maxTicks != Path::REPEAT) {
				return true;
			}
			return false;
		}
		
		void modify() {
			*this->target += this->delta;
		}
		
};
