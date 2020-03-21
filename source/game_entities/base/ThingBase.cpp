#include "ThingBase.h"

ThingBase::ThingBase(int flags) : absoluteFlags(flags), flags(flags) {}

ThingBase::~ThingBase() {}

void ThingBase::setParent(GameInstance* parent) {
	this->parent = parent;
}

int ThingBase::getAbsoluteFlags() const {
	return this->flags;
}

int ThingBase::getFlags() const {
	return this->flags;
}

void ThingBase::addNodes() {}

void ThingBase::unsetFlag(ENTITY_FLAG flag) {
	if (this->flags & flag) {
		this->flags &= ~flag;
	}
}

void ThingBase::setFlag(ENTITY_FLAG flag) {
	if (!(this->flags & flag)) {
		this->flags |= flag;
	}
}

ENTITY_DIRECTION getDirectionFromAngle(double angle) {
	while (angle < 0 || angle > 2 * M_PI) {
		if (angle < 0) {
			angle += 2 * M_PI;
		} else if (angle > 2 * M_PI) {
			angle -= 2 * M_PI;
		}
	}
	if (angle > M_PI_8 && angle < M_PI_4 + M_PI_8) {
		return UP_RIGHT;
	} else if (angle > M_PI_4 + M_PI_8 && angle < M_PI_2 + M_PI_8) {
		return UP;
	} else if (angle > M_PI_2 + M_PI_8 && angle < M_PI - M_PI_8) {
		return UP_LEFT;
	} else if (angle > M_PI - M_PI_8 && angle < M_PI + M_PI_8) {
		return LEFT;
	} else if (angle > M_PI + M_PI_8 && angle < M_PI + M_PI_2 - M_PI_8) {
		return DOWN_LEFT;
	} else if (angle > M_PI + M_PI_2 - M_PI_8 && angle < M_PI + M_PI_2 + M_PI_8) {
		return DOWN;
	} else if (angle > M_PI + M_PI_2 + M_PI_8 && angle < 2 * M_PI - M_PI_8){
		return DOWN_RIGHT;
	} else {
		return RIGHT;
	}
}
