#include "ThingBase.h"
#include "../../GameInstance.h"

ThingBase::ThingBase(int flags) : absoluteFlags(flags), flags(flags), owner(NULL), parent(NULL) {}

ThingBase::~ThingBase() {}

int ThingBase::getAbsoluteFlags() const {
	return this->flags;
}

int ThingBase::getFlags() const {
	return this->flags;
}

bool ThingBase::isAlive() const {
	return true;
}

std::size_t ThingBase::hash() const {
	return ((long long) this) >> 5;
}

std::vector<ThingPtr>& ThingBase::getMyThings() {
	return this->myThings;
}

void ThingBase::ping(const std::string& info, const double& data) {
	Point p = this->getPosition();
	logTimeNow();
	printf("[PingLog] %p at (%.2f, %.2f) pinged with message '%s' and the data of '%.3f'\n", (void*) this, p.x, p.y, info.c_str(), data);
	fflush(stdout);
	this->pingInternal(info, data);
}

void ThingBase::pingInternal([[maybe_unused]] const std::string& info, [[maybe_unused]] const double& data) {}

void ThingBase::setFlag(ENTITY_FLAG flag) {
	if (!(this->flags & flag)) this->flags |= flag;
}

void ThingBase::setOwner(ThingBase* owner) {
	if (!this->owner) this->owner = owner;
}

void ThingBase::setParent(GameInstance* parent) {
	if (!this->parent) this->parent = parent;
}

void ThingBase::unsetFlag(ENTITY_FLAG flag) {
	if (this->flags & flag) this->flags &= ~flag;
}

void ThingBase::update() {}

ENTITY_DIRECTION getDirectionFromAngle(double angle) {
	while (angle < 0 || angle > 2 * M_PI) {
		if (angle < 0) {
			angle += 2 * M_PI;
		} else if (angle > 2 * M_PI) {
			angle -= 2 * M_PI;
		}
	}
	// Uhhhhhhhhhhh ignore this 
	if (angle > M_PI_8 && angle < M_PI_4 + M_PI_8) {
		return DOWN_RIGHT;
	} else if (angle > M_PI_4 + M_PI_8 && angle < M_PI_2 + M_PI_8) {
		return DOWN;
	} else if (angle > M_PI_2 + M_PI_8 && angle < M_PI - M_PI_8) {
		return DOWN_LEFT;
	} else if (angle > M_PI - M_PI_8 && angle < M_PI + M_PI_8) {
		return LEFT;
	} else if (angle > M_PI + M_PI_8 && angle < M_PI + M_PI_2 - M_PI_8) {
		return UP_LEFT;
	} else if (angle > M_PI + M_PI_2 - M_PI_8 && angle < M_PI + M_PI_2 + M_PI_8) {
		return UP;
	} else if (angle > M_PI + M_PI_2 + M_PI_8 && angle < 2 * M_PI - M_PI_8){
		return UP_RIGHT;
	} else {
		return RIGHT;
	}
}
