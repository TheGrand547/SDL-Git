#include "PositionLock.h"

PositionLock::PositionLock(Point& initial) : reference(initial), value(initial), initial(initial) {}

PositionLock::~PositionLock() {}

double PositionLock::absoluteDistance() const {
	return this->reference.distanceToPoint(this->value);
}

double PositionLock::fastDistance() const {
	return this->reference.fastDistanceToPoint(this->value);
}

Point PositionLock::delta() const {
	return this->reference - this->initial;
}

void PositionLock::update() {
	this->value = this->reference;
}

void PositionLock::revert() {
	this->reference = this->value;
}
