#include "CirclePath.h"

CirclePath::CirclePath() : Path() {
	this->outsideMult = 0;
	this->periodModify = 0;
}

CirclePath::CirclePath(int radius, float periodModify, int maxTicks, bool clockwise, int startingTicks) : Path() {
	// TODO: Make this class functional
	this->outsideMult = radius * pow(periodModify, 2.0);
	this->periodModify = periodModify;
	
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
	this->ticksDone = startingTicks;
	
	/* Kind of messy stuff for looping */
	this->startingTicks = int(startingTicks);
	this->startingMaxTicks = int(this->maxTicks);
};

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
	if (this->ticksDone >= this->maxTicks && this->maxTicks != Path::REPEAT) {
		return true;
	}
	return false;
}

void CirclePath::modify(float time) {
	float tempdx = (this->outsideMult) * cos(this->ticksDone * M_PI / 180.f * this->periodModify);
	float tempdy = (this->plot * this->outsideMult) * sin(this->ticksDone * M_PI / 180.f * this->periodModify);
	this->target->accelerate(PointDelta(Point(tempdx, tempdy) * time, 1));
	this->ticksDone += 6 * time;
}
