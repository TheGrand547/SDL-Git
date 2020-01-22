#pragma once
#ifndef ENTITY_BASE_H
#define ENTITY_BASE_H
#include "../../primitives/Point.h"
#include "../../primitives/PointDelta.h"
#include "../../wrappers/Timer.h"

enum ENTITY_FLAGS {
	SOLID         = 0x0001, // Other objects can collide with this
	NOCLIP        = 0x0002, // This doesn't collide with others
	TRIGGER       = 0x0004, // Trigger event based on data when something happens	
};

/* Base class for entities that exist for extended periods of time
 * with more complicated behavior patterns than a particle */
class EntityBase {
	protected:
		double frictionAmount, angle;
		Timer timer;
		PointDelta velocity;
		Point acceleration;
	public:
		int flags;
		EntityBase(int flags = SOLID, double maxVelocity = 4, double friction = 10.0); // TODO: Constant these
		~EntityBase();
		void evalAngle(Point delta);
		void accelerate(PointDelta delta);
};
#endif
