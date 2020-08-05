#pragma once
#ifndef ENTITY_BASE_H
#define ENTITY_BASE_H
#include "../../essential/util.h"
#include "../../GameInstance.h"
#include "../../primitives/Point.h"
#include "../../primitives/Rect.h"
#include "../../wrappers/MovementWrapper.h"
#include "../../wrappers/Timer.h"
#include "ThingBase.h"

/* Base class for entities that exist for extended periods of time
 * with more complicated behavior patterns than a particle */
class EntityBase : public ThingBase {
	protected:
		// TODO: Friction should be based on math, do this at some point
		double angle, frictionAmount, maxVelocity;
		MovementWrapper movement;
		Point acceleration, velocity;
	public:
		EntityBase(int flags);
		~EntityBase();
		double originDistance() const override;
		void accelerate(const Point& delta);
		void evalAngle(const Point& delta);
		void setAngle(const double& angle);
		void setFriction(const double& value);
		void setMaxVelocity(const double& value);
};
#endif
