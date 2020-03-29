#include "MovementWrapper.h"

MovementWrapper::MovementWrapper() {
	this->timer.start();
}

MovementWrapper::~MovementWrapper() {}

double MovementWrapper::getValue() {
	double ticks = this->timer.getTicks();
	if (ticks) {
		ticks /= 1000.f;
		this->timer.start();
	}
	return ticks;
}
