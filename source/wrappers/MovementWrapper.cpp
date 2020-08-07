#include "MovementWrapper.h"

MovementWrapper::MovementWrapper() {}

MovementWrapper::~MovementWrapper() {}

double MovementWrapper::getValue() {
	if (!this->timer.isStarted()) this->timer.start();
	double ticks = this->timer.getTicks();
	if (ticks) {
		ticks /= 1000.f;
		this->timer.start();
	}
	return ticks;
}
