#pragma once
#ifndef POLYGON_H
#define POLYGON_H

class Rect;

#include "../Color.h"
#include "Line.h"
#include "Point.h"
#include <iostream>
#include <vector>

struct Polygon : public Color {
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
	virtual bool overlap(const Polygon& other) const;
	virtual int numberOfCollisions(const Line& line) const;
	virtual Point collideLine(const Line& ray) const;
	virtual Rect getBoundingRect() const;
	virtual void draw(Renderer renderer);
	virtual void draw(SDL_Renderer* renderer, Point offset);

	bool operator==(const Polygon& other) const;
	bool operator!=(const Polygon& other) const;
};

std::ostream& operator<<(std::ostream& output, const Polygon& poly);
#endif
