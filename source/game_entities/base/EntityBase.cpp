#include "EntityBase.h"
#include "../../essential/util.h"


EntityBase::EntityBase(int flags) : ThingBase(flags), angle(0), frictionAmount(1), maxVelocity(0), acceleration(0, 0), velocity(0, 0) {}

EntityBase::~EntityBase() {}

double EntityBase::originDistance() const {
	return this->position.distanceToPoint(Point(0, 0));
}

void EntityBase::accelerate(const Point& delta) {
	// "Good enough" formula
	Point copy = delta * this->maxVelocity;
	double value = this->movement.getValue();

	if (isZero(delta.x)) copy -= Point(this->velocity.x, 0);
	if (isZero(delta.y)) copy -= Point(0, this->velocity.y);

	this->acceleration = copy * value * 5;
	this->velocity += this->acceleration;
	if (this->velocity.getMagnitude() > this->maxVelocity) this->velocity = this->velocity.getUnitVector() * this->maxVelocity;
	this->evalAngle(this->velocity);
}

void EntityBase::evalAngle(const Point& delta) {
	if (delta.getNonZero() && delta.isReal()) this->angle = atan2(delta.y, delta.x);
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
