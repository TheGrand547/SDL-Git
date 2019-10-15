#pragma once
#ifndef ENTITY_BASE_H
#define ENTITY_BASE_H
#include "../../primitives/Point.h"
#include "../../primitives/PointDelta.h"
class EntityBase {
	protected:
		PointDelta velocity
		Point acceleration;
		double frictionAmount;
	public:
		EntityBase(double maxVelocity = 4, double friction = -10.0); // TODO: Constant these
		~EntityBase();
		void accelerate(Point delta);
		virtual void move(Point delta) = 0;
};
#endif
