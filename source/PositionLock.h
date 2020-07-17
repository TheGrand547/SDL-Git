#pragma once
#ifndef POSITION_LOCK_H
#define POSITION_LOCK_H
#include "primitives/Point.h"

class PositionLock {
	private:
		Point& reference;
		Point value;
		const Point initial;
	public:
		PositionLock(Point& initial);
		~PositionLock();
		double absoluteDistance() const;
		double fastDistance() const;
		Point delta() const;
		void revert();
		void update();
};
#endif
