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
