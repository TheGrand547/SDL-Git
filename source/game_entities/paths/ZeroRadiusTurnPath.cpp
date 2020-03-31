#include "ZeroRadiusTurnPath.h"

ZeroRadiusTurnPath::ZeroRadiusTurnPath(float targetAngle, float time, bool clockwise) : Path(), targetAngle(targetAngle), clockwise(clockwise) {
	this->maxTicks = time / 10;
}

ZeroRadiusTurnPath::~ZeroRadiusTurnPath() {}

bool ZeroRadiusTurnPath::isFinished() const {
	return this->ticksDone >= this->maxTicks;
}

void ZeroRadiusTurnPath::start() {
	this->startingAngle = this->target->getAngle();
	this->timer.start();
	this->ticksDone = 0;
	this->started = true;
	this->target->toggleTurn();
}

void ZeroRadiusTurnPath::stop() {
	this->timer.stop();
	this->target->toggleTurn();
	this->started = false;
}

void ZeroRadiusTurnPath::modify(float delta) {
	float deltaAngle = (this->targetAngle - this->startingAngle) / (this->maxTicks * 10);
	if (this-clockwise) {
		this->target->turn(-deltaAngle);
	} else {
		this->target->turn(deltaAngle);
	}
	this->ticksDone += delta;
	this->target->move(PointDelta(0, 0, 0));
}
