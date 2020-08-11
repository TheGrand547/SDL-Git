#pragma once
#ifndef POLYGON_H
#define POLYGON_H

class Rect;

#include "../Color.h"
#include "Line.h"
#include "Point.h"
#include<vector>

class Polygon : public Color {
	public:
		virtual ~Polygon();
		virtual bool isReal() const = 0;
		virtual double getArea() const = 0;
		virtual int numLines() const = 0;
		virtual int numPoints() const = 0;
		virtual Point getCenter() const = 0;
		virtual std::vector<Line> getLines() const = 0;
		virtual std::vector<Point> getPoints() const = 0;
		
		virtual bool containsPoint(const Point& point) const;
		virtual bool doesLineCollide(const Line& line) const;
		virtual bool isAxisAligned() const;
		virtual int numberOfCollisions(const Line& line) const;
		virtual Point collideLine(const Line& ray) const;
		virtual void draw(SDL_Renderer* renderer, Point offset);
		
		bool operator==(const Polygon& other) const;
		bool overlap(const Polygon& other) const;
		Rect getBoundingRect() const;
};
#endif
