#pragma once
#include<math.h>
#include "../../wrappers/Timer.h"
#include "Path.h"

template<class T>
class CirclePath : public Path<T> {
	protected:
		/* Standard Parametric Equation for a Cirle
		 * x = r * cos(t / a)
		 * y = r * sin(t / a)
		 * When CirclePath is created by a PathManager, its stored somewhere not doing anything
		 * When PathManager calls a Path it is then updated every frame until isFinished() returns false
		 * When called it checks how many milliseconds it has been since it was called, and if that number is 
		 * greater than 10ms it runs an update. Updates are defined as such
		 * dx = r / a * -sin(t / a)
		 * dy = r / a * cos(t / a)
		 * Where r is the intended radius and 2pi * a is the period */
		float outsideMult, periodModify;
		int maxTicks, plot;
		
		/* Messy stuff for proper looping */
		int startingTicks = 0;
		int startingMaxTicks = 0;
	public:
		CirclePath() : Path<T>(NULL) {
			this->outsideMult = 0;
			this->periodModify = 0;
		}
	
		CirclePath(int radius = 10, float periodModify = .5, int maxTicks = Path<T>::SINGLE_LOOP, bool clockwise = true, int startingTicks = 0) : Path<T>() {
			this->outsideMult = sqrt(radius * periodModify);
			this->periodModify = periodModify;
			
			if (maxTicks == Path<T>::SINGLE_LOOP) {
				this->maxTicks = 360 / periodModify;
			} else if (maxTicks == Path<T>::REPEAT) {
				this->maxTicks = Path<T>::REPEAT;
			} else {
				this->maxTicks = maxTicks + startingTicks;
			}
			if (!clockwise) {
				this->plot = -1;
			} else {
				this->plot = 1;
			}
			this->ticksDone += startingTicks;
			
			/* Kind of messy stuff for looping */
			this->startingTicks = int(startingTicks);
			this->startingMaxTicks = int(this->maxTicks);
		};
		
		~CirclePath() {}
		
		void stop() {
			this->maxTicks = this->startingMaxTicks;
			this->ticksDone = this->startingTicks;
			this->timer->stop();
		}
		
		bool isFinished() {
			if (this->ticksDone >= this->maxTicks && this->maxTicks != Path<T>::REPEAT) {
				return true;
			}
			return false;
		}
		
		void modify() {
			float tempdx = (-this->outsideMult) * sin(this->ticksDone * M_PI / 180.f * this->periodModify);
			float tempdy = (this->plot * this->outsideMult) * cos(this->ticksDone * M_PI / 180.f * this->periodModify);
			*this->target += Point(tempdx, tempdy);
			this->ticksDone += 5; //This is stupidly sloppy, and despite knowing it *has* to be done it still pisses me off to no end
		}
};
