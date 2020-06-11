#include "EntityBase.h"

EntityBase::EntityBase(int flags) : ThingBase(flags), frictionAmount(1), angle(0), acceleration(0, 0), velocity(0, 0, 0) {}

EntityBase::~EntityBase() {}

double EntityBase::originDistance() const {
	return this->position.distanceToPoint(Point(0, 0));
}

void EntityBase::setAngle(const double angle) {
	this->angle = angle;
}

void EntityBase::setFriction(const double value) {
	this->frictionAmount = abs(value);
}

void EntityBase::setMaxVelocity(const double value) {
	this->velocity = PointDelta(0, 0, value);
}

void EntityBase::evalAngle(Point delta) {
	if (delta.getNonZero()) {
		this->angle = atan2(delta.y, delta.x);
	}
}

void EntityBase::accelerate(PointDelta delta) {
	this->timer.tick();
	if (abs(delta.x) < 0.0001) {
		delta -= Point(this->velocity.x, 0) / this->frictionAmount;
	}
	if (abs(delta.y) < 0.0001) {
		delta -= Point(0, this->velocity.y) / this->frictionAmount;
	}
	this->acceleration = delta * this->timer.getRatio();
	this->velocity += this->acceleration;
	this->evalAngle(this->velocity);
}
