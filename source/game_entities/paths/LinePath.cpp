#include "LinePath.h"
#include<iostream> // DIE
LinePath::LinePath() : Path() {
	this->delta = Point(0, 0);
	this->maxTicks = 1;
}

LinePath::LinePath(Point vector, float tickTime, int repeatCount) : Path() {
	this->delta = vector / (tickTime / 10);
	if (repeatCount == Path::SINGLE_LOOP) {
		this->maxTicks = tickTime / 10;
	} else {
		this->maxTicks = repeatCount * tickTime / 10;
	}
}

LinePath::~LinePath() {}

// Tick time is the duration in milliseconds, which must be adjusted for the refresh rate of paths
LinePath::LinePath(Point startingPos, Point endingPos, float tickTime, int repeatCount) : Path() {
	*this = LinePath(endingPos - startingPos, tickTime, repeatCount);
}

void LinePath::stop() {
	this->ticksDone = 0;
	this->timer.stop();
}

bool LinePath::isFinished() {
	if (this->ticksDone >= this->maxTicks && this->maxTicks != Path::REPEAT) {
		return true;
	}
	return false;
}

void LinePath::modify(float time) {
	this->target->move(this->delta * time);
	this->ticksDone += time;
}
