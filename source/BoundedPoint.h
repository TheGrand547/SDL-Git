#pragma once
#include "primitives/Point.h"

struct BoundedPoint : public Point {
	double xMax, yMax;
	BoundedPoint();
	BoundedPoint(double xMax, double yMax);
	BoundedPoint(double xpos, double ypos, double maxX, double maxY);
	BoundedPoint(Point position, double xMax, double yMax);
	BoundedPoint(const BoundedPoint& other);
	BoundedPoint& operator=(const BoundedPoint& other);
	~BoundedPoint();
	void maxX();
	void maxY();
	void operator+=(Point delta);
	void operator-=(Point delta);
	void reduce();
};
