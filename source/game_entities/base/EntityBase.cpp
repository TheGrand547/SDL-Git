#include "EntityBase.h"

EntityBase::EntityBase(int flags) : ThingBase(flags), angle(0), frictionAmount(1), maxVelocity(0), acceleration(0, 0), velocity(0, 0) {}

EntityBase::~EntityBase() {}

double EntityBase::originDistance() const {
	return this->position.distanceToPoint(Point(0, 0));
}

void EntityBase::setAngle(const double& angle) {
	this->angle = angle;
}

void EntityBase::setFriction(const double& value) {
	this->frictionAmount = abs(value);
}

void EntityBase::setMaxVelocity(const double& value) {
	this->maxVelocity = value;
}

void EntityBase::evalAngle(const Point& delta) {
	if (delta.getNonZero() && delta.isReal()) {
		this->angle = atan2(delta.y, delta.x);
	}
}

void EntityBase::accelerate(const Point& delta) {
	// "Good enough" formula
	Point copy = delta * this->maxVelocity / pow(this->frictionAmount, 1.15);
	this->timer.tick();
	if (abs(delta.x) < ROUNDING) {
		copy -= Point(this->velocity.x, 0) / this->frictionAmount;
	}
	if (abs(delta.y) < ROUNDING) {
		copy -= Point(0, this->velocity.y) / this->frictionAmount;
	}
	this->acceleration = copy * this->timer.getRatio();
	this->velocity += this->acceleration;
	if (this->velocity.getMagnitude() > this->maxVelocity) this->velocity = this->velocity.getUnitVector() * this->maxVelocity;
	this->evalAngle(this->velocity);
}
