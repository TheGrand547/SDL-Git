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
		virtual ~Polygon();
		virtual bool containsPoint(const Point& point) const = 0;
		virtual bool doesLineCollide(const Line& line) const = 0;
		virtual int numberOfCollisions(const Line& line) const = 0;
		virtual int numLines() const = 0;
		virtual int numPoints() const = 0;
		virtual Point collideLine(const Line& ray) const = 0;
		virtual Point getCenter() const = 0;
		virtual std::vector<Line> getLines() const = 0;
		virtual std::vector<Point> getPoints() const = 0;
		virtual void draw(SDL_Renderer* renderer, Point offset) = 0;
		
		virtual bool isAxisAligned() const;
		
		bool operator==(const Polygon& other) const;
		bool overlap(const Polygon& other) const;
		Rect getBoundingRect() const;
};
#endif
