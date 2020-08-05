#include "ZeroRadiusTurnPath.h"

ZeroRadiusTurnPath::ZeroRadiusTurnPath(double targetAngle, double time, bool clockwise) : Path(), clockwise(clockwise), maxTicks(time / 10), 
										targetAngle(targetAngle) {}

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

void ZeroRadiusTurnPath::modify(double delta) {
	// TODO: Update this to 'modern standards'
	double deltaAngle = (this->targetAngle - this->startingAngle) / (this->maxTicks * 10);
	this->target->turn(deltaAngle * ((this->clockwise) ? -1 : 1));
	this->ticksDone += delta;
	this->target->move(Point(0, 0));
}
