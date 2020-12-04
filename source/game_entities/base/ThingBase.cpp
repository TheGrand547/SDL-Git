#include "ThingBase.h"
#include "../../GameInstance.h"

// TODO: This is bad
ThingBase::ThingBase(int flags) : angle(0.0 / 0.0), absoluteFlags(flags), flags(flags), owner(NULL),
									hashValue(((long long) this) >> ((SDL_GetTicks() % 5) * 4) % 7), parent(NULL) {}

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

double ThingBase::getAngle() const {
	return this->angle;
}

std::size_t ThingBase::hash() const {
	return this->hashValue;
}

std::vector<ThingPtr>& ThingBase::getMyThings() {
	return this->myThings;
}

void ThingBase::ping(const std::string& info, const double& data) {
	Point p = this->getPosition();
	logFormat(__FILE__, __PRETTY_FUNCTION__, "Ping", __LINE__);
	printf("%p at (%.2f, %.2f) pinged with message '%s' and the data of '%.3f'\n", (void*) this, p.x, p.y, info.c_str(), data);
	fflush(stdout);
	this->pingInternal(info, data);
}

void ThingBase::pingInternal([[maybe_unused]] const std::string& info, [[maybe_unused]] const double& data) {}

void ThingBase::setAngle(const Point& point) {
	this->angle = point.getAngle();
}

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

double getAngleFromDirection(const ENTITY_DIRECTION& direction) {
	double angle = 0;
	switch (direction) {
		case RIGHT:
			break;
		case UP_RIGHT: 
			angle = M_PI_4;
			break;
		case UP:
			angle = M_PI_2;
			break;
		case UP_LEFT:
			angle = M_PI_2 + M_PI_4;
			break;
		case LEFT:
			angle = M_PI;
			break;
		case DOWN_LEFT:
			angle = M_PI + M_PI_4;
			break;
		case DOWN:
			angle = M_PI + M_PI_2;
			break;
		case DOWN_RIGHT:
			angle = M_PI + M_PI_2 + M_PI_4;
			break;
	}
	return angle;
}

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

std::size_t std::hash<ThingPtr>::operator()(const ThingPtr& thing) const noexcept {
	if (!thing) return 0;
	return thing->hash();
}
