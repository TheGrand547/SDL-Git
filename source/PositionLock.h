#pragma once
#ifndef POSITION_LOCK_H
#define POSITION_LOCK_H
#include "primitives/Point.h"

class PositionLock {
	protected:
		bool locked;
		Point& reference;
		const Point value;
	public:
		PositionLock(Point& initial);
		~PositionLock();
		void unlock();
};
#endif
