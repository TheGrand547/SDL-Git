#pragma once
#include "primitives/Point.h"

class BoundedPoint : public Point {
	private:
		float xMin, xMax;
		float yMin, yMax;
	public:
		BoundedPoint();
		BoundedPoint(float xMax, float yMax);
		BoundedPoint(float xpos, float ypos, float xMin, float yMin, float xMax, float yMax);
		BoundedPoint(Point pos, float xMin, float yMin, float xMax, float yMax);
		BoundedPoint(const BoundedPoint &other);
		BoundedPoint &operator=(BoundedPoint other);
		~BoundedPoint();
		void reduce();
		void operator+=(Point delta);
		void operator-=(Point delta);
		void zeroX();
		void zeroY();
		void maxX();
		void maxY();
};
