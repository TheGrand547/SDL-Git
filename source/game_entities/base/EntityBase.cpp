#include "EntityBase.h"

EntityBase::EntityBase(double maxVelocity, double friction) : this->frictionAmount(friction) {
	this->velocity = PointDelta(0, 0, maxVelocity);
}

EntityBase::~EntityBase() {}

void EntityBase::accelerate(Point delta) {
	if (acceleration.getMagnitude() < 0.1) {
		acceleration = this->velocity / this->frictionAmount;
	}
	this->acceleration = acceleration * this->f->getRatio();
	this->velocity += this->acceleration;
}
