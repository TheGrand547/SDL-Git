#include "ThingBase.h"

ThingBase::~ThingBase() {}

void ThingBase::setParent(GameInstance* parent) {
	this->parent = parent;
}

int ThingBase::getFlags() const {
	return this->flags;
}

Point ThingBase::getPosition() const {
	return this->position;
}
