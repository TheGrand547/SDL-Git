#pragma once
#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "Polygon.h"

class Triangle : public Polygon {
	protected:
		Point a, b, c;
	public:
		Triangle();
		Triangle(Point a, Point b, Point c);
		~Triangle();
		bool isReal() const override;
		double getArea() const override;
		int numLines() const override;
		int numPoints() const override;
		Point getCenter() const override;
		std::vector<Line> getLines() const override;
		std::vector<Point> getPoints() const override;
};
#endif
