#pragma once
#include "Path.h"
#include "../../primitives/Point.h"

float toTicks(float seconds) {
	return seconds * 1000.f;
}
template<class T>
class LinePath : public Path<T> {
	private:
		Point delta;
		int maxTicks;
	public:
		LinePath() : Path<T>() {
			this->delta = Point(0, 0);
			this->maxTicks = 1;
		}
		
		LinePath(Point vector, float tickTime, int repeatCount = Path<T>::SINGLE_LOOP) : Path<T>() {
			this->delta = vector / (tickTime / 10);
			if (repeatCount == Path<T>::SINGLE_LOOP) {
				this->maxTicks = tickTime / 10;
			} else {
				this->maxTicks = repeatCount * tickTime / 10;
			}
		}
		
		/* Tick time is the duration in milliseconds, which must be adjusted for the refresh rate of paths */
		
		LinePath(Point startingPos, Point endingPos, int tickTime, int repeatCount = Path<T>::SINGLE_LOOP) : Path<T>() {
			*this = LinePath<T>(endingPos-startingPos, tickTime, repeatCount);
		}
		
		void stop() {
			this->ticksDone = 0;
			this->timer->stop();
		}
		
		bool isFinished() {
			if (this->ticksDone >= this->maxTicks && this->maxTicks != Path<T>::REPEAT) {
				return true;
			}
			return false;
		}
		
		void modify() {
			*this->target += this->delta;
		}
		
};
