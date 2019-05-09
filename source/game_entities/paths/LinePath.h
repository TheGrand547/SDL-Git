#pragma once
#include "Path.h"
#include "../../primatives/Point.h"

float toTicks(float seconds) {
	return seconds * 1000.f;
}

class LinePath : public Path<Point> {
	private:
		Point delta;
		int maxTicks;
	public:
		LinePath() : Path<Point>(NULL) {
			this->delta = Point(0, 0);
			this->maxTicks = 1;
		}
		
		LinePath(Point* target, Point vector, float tickTime, int repeatCount = Path::SINGLE_LOOP) : Path<Point>(target) {
			this->delta = vector / (tickTime / 10);
			if (repeatCount == Path::SINGLE_LOOP) {
				this->maxTicks = tickTime / 10;
			} else {
				this->maxTicks = repeatCount * tickTime / 10;
			}
		}
		
		/* Tick time is the duration in milliseconds, which must be adjusted for the refresh rate of paths */
		
		LinePath(Point* target, Point startingPos, Point endingPos, int tickTime, int repeatCount = Path::SINGLE_LOOP) : Path<Point>(target) {
			*this = LinePath(target, endingPos-startingPos, tickTime, repeatCount);
		}
		
		void stop() {
			this->ticksDone = 0;
			this->timer->stop();
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
