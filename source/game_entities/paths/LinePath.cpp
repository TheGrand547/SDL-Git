#include "LinePath.h"

LinePath::LinePath() : Path() {
	// TODO: Log error in initialization
	this->delta = PointDelta(0, 0, 0);
	this->maxTicks = 0;
}

LinePath::LinePath(PointDelta vector, float distance, int repeatCount) {
	this->delta = vector;
	if (repeatCount == Path::SINGLE_LOOP) {
		this->maxTicks = distance;
	} else {
		this->maxTicks = repeatCount * distance;
	}
}

LinePath::~LinePath() {}

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
	this->target->accelerate(this->delta);
	this->ticksDone += this->delta.getMagnitude() * time;
}
