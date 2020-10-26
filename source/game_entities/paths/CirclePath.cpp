#include "CirclePath.h"
#include <math.h>


CirclePath::CirclePath() : Path(), outsideMult(0), periodModify(0), maxTicks(0), plot(0), startingMaxTicks(0), startingTicks(0) {
	this->ticksDone = 0;
}

CirclePath::CirclePath(int radius, double periodModify, int maxTicks, bool clockwise, int startingTicks) : Path(), 
						outsideMult(radius * pow(periodModify, 2.0)), periodModify(periodModify), startingTicks(startingTicks) {
	// TODO: Make this class functional
	this->outsideMult = radius * pow(periodModify, 2.0);
	this->ticksDone = startingTicks;
	if (maxTicks == Path::SINGLE_LOOP) {
		this->maxTicks = 360 / periodModify;
	} else if (maxTicks == Path::REPEAT) {
		this->maxTicks = Path::REPEAT;
	} else {
		this->maxTicks = maxTicks + startingTicks;
	}
	if (!clockwise) {
		this->plot = -1;
	} else {
		this->plot = 1;
	}
}

CirclePath::~CirclePath() {}

void CirclePath::stop() {
	this->maxTicks = this->startingMaxTicks;
	this->ticksDone = this->startingTicks;
	this->timer.stop();
	this->started = false;
}

void CirclePath::start() {
	this->ticksDone = this->startingTicks;
	this->timer.start();
	this->started = true;
}

bool CirclePath::isFinished() const {
	return this->maxTicks != Path::REPEAT && this->ticksDone >= this->maxTicks;
}

void CirclePath::modify(double time) {
	double tempdx = (this->outsideMult) * cos(this->ticksDone * M_PI / 180.f * this->periodModify);
	double tempdy = (this->plot * this->outsideMult) * sin(this->ticksDone * M_PI / 180.f * this->periodModify);
	this->target->move(Point(tempdx, tempdy) * time);
	this->ticksDone += 6 * time;
}
