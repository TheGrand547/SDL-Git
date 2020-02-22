#include "ThingBase.h"

ThingBase::~ThingBase() {}

void ThingBase::setParent(GameInstance* parent) {
	this->parent = parent;
}

int ThingBase::getFlags() const {
	return this->flags;
}

void ThingBase::addNodes() {}

