#include "PositionLock.h"

PositionLock::PositionLock(Point& initial) : locked(true), reference(initial), value(initial) {}

PositionLock::~PositionLock() {
	if (this->locked) {
		this->reference = this->value;
	}
}

void PositionLock::unlock() {
	this->locked = false;
}
