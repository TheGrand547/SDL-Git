#pragma once
#ifndef ENTITY_BASE_H
#define ENTITY_BASE_H
#include "../../GameInstance.h"
#include "../../primitives/Point.h"
#include "../../primitives/PointDelta.h"
#include "../../wrappers/Timer.h"
#include "ThingBase.h"

/* Base class for entities that exist for extended periods of time
 * with more complicated behavior patterns than a particle */
class EntityBase : public ThingBase {
	protected:
		double frictionAmount, angle;
		Point acceleration;
		PointDelta velocity;
		Timer timer;
	public:
		EntityBase(double maxVelocity = 4, double friction = 10.0); // TODO: Constant these
		~EntityBase();
		float originDistance() const override;
		void accelerate(PointDelta delta);
		void evalAngle(Point delta);
};
#endif
