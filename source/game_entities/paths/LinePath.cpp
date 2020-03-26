#include "LinePath.h"

LinePath::LinePath() : Path() {
	// TODO: Log error in initialization
	this->maxTicks = 0;
}

LinePath::LinePath(Point vector, float distance, int repeatCount) : Path(), delta(vector)  {
	if (repeatCount == Path::SINGLE_LOOP) {
		this->maxTicks = distance;
	} else {
		this->maxTicks = repeatCount * distance;
	}
}

LinePath::~LinePath() {}

void LinePath::start() {
	this->timer.start();
	this->begin = this->target->getPosition();
	this->ticksDone = 0;
	this->started = true;
}

void LinePath::stop() {
	this->timer.stop();
	this->begin = this->target->getPosition();
	this->ticksDone = 0;
	this->started = false;
}

bool LinePath::isFinished() const {
	return this->maxTicks != Path::REPEAT && this->begin.distanceToPoint(this->target->getPosition()) >= this->maxTicks;
}

void LinePath::modify(float time) {
	time++;
	this->target->move(this->delta);
}
