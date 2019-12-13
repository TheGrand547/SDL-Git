#include "LinePath.h"

LinePath::LinePath() : Path() {
	// TODO: Log error in initialization
	this->delta = PointDelta(0, 0, 0);
	this->maxTicks = 0;
}

LinePath::LinePath(PointDelta vector, float distance, int repeatCount) : Path() {
	this->delta = vector;
	if (repeatCount == Path::SINGLE_LOOP) {
		this->maxTicks = distance;
	} else {
		this->maxTicks = repeatCount * distance;
	}
}

LinePath::~LinePath() {}

void LinePath::start() {
	this->timer.start();
	this->begin = this->target->getPos();
	this->ticksDone = 0;
	this->started = true;
}

void LinePath::stop() {
	this->timer.stop();
	this->begin = this->target->getPos();
	this->ticksDone = 0;
	this->started = false;
}

bool LinePath::isFinished() const {
	if (this->begin.distanceToPoint(this->target->getPos()) >= this->maxTicks && this->maxTicks != Path::REPEAT) {
		return true;
	}
	return false;
}

void LinePath::modify(float time) {
	this->target->accelerate(this->delta);
}
