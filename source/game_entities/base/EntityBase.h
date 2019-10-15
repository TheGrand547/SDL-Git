#pragma once
#ifndef ENTITY_BASE_H
#define ENTITY_BASE_H
#include "../../primitives/Point.h"
#include "../../primitives/PointDelta.h"
#include "../../wrappers/Timer.h"
class EntityBase {
	protected:
		double frictionAmount, angle;
		Timer timer;
		PointDelta velocity;
		Point acceleration;
	public:
		EntityBase(double maxVelocity = 4, double friction = -10.0); // TODO: Constant these
		~EntityBase();
		void evalAngle(Point delta);
		void accelerate(PointDelta delta);
};
#endif
