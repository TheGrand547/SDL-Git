#pragma once
#ifndef POLYGON_H
#define POLYGON_H

class Rect;

#include<vector>
#include "../MyBase.h"
#include "Line.h"
#include "Point.h"

class Polygon : public MyBase {
	public:
		virtual Point collideLine(const Line& ray) const = 0;
		virtual bool containsPoint(const Point& point) const = 0;
		virtual bool doesLineCollide(const Line& line) const = 0;
		virtual bool operator==(const Polygon& other) const = 0;
		virtual bool overlap(const Polygon& other) const = 0;
		virtual int numberOfCollisions(const Line& line) const = 0;
		virtual std::vector<Line> getLines() const = 0;
		virtual std::vector<Point> getPoints() const = 0;
		Rect getBoundingRect() const;
};
#endif
