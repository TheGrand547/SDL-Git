#include "EntityBase.h"

EntityBase::EntityBase(double maxVelocity, double friction) {
	this->acceleration = Point(0, 0);
	this->angle = 0;
	this->frictionAmount = friction;
	this->velocity = PointDelta(0, 0, maxVelocity);
}

EntityBase::~EntityBase() {}

void EntityBase::evalAngle(Point delta) {
	this->angle = atan2(delta.y(), delta.x());
}

void EntityBase::accelerate(PointDelta delta) {
	this->timer.tick();
	if (delta.getMagnitude() < 0.1) { // Maybe constant this?
		delta = this->velocity / this->frictionAmount;
	}
	this->acceleration = delta * this->timer.getRatio();
	this->velocity += this->acceleration;
	this->evalAngle(this->velocity);
}
