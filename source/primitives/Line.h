#pragma once
#ifndef LINE_H
#define LINE_H
#include "../essential/misc.h"
#include "../essential/util.h"
#include "../essential/SDL_Headers.h"
#include "../Color.h"
#include <cassert>
#include <cmath>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>

class Line: public Color {
	// Represents a line segment in the form, ax+by=c, bounded by the points A and B
	private:
		Point originPoint, endingPoint;
	public:	
		Line(Point pointA = Point(), Point pointB = Point(), Uint8 r = 0x00, Uint8 g = 0x00, Uint8 b = 0xFF, Uint8 a = 0xFF);
		~Line();
		Line(const Line& line);
		Line& operator=(const Line& that);
		bool isCollinear(const Line& other) const;
		bool isOrthogonal(const Line& other) const;
		bool isParallel(const Line& other) const;
		bool isPointOnThisLine(const Point& point) const;
		bool collidePoint(const Point& point) const;
		bool shareNoPoints(const Line& other) const;
		void operator+=(const Point& point);
		void operator-=(const Point& point);
		void operator+=(const double& num) = delete;
		void operator-=(const double& num) = delete;
		Line operator*(const double& delta) const;
		Line operator/(const double& delta) const;
		Line operator+(const Point& point) const;
		Line operator-(const Point& point) const;
		Line operator+(const double& num) = delete;
		Line operator-(const double& num) = delete;
		double getAx() const;
		double getBy() const;
		double getC() const;
		double getFastMagnitude() const;
		double getMagnitude() const;
		Point getEnd() const;
		Point getOrigin() const;
		Point getUnitVector() const;
		Point getVector() const;
		Point intersectionPoint(const Line& other) const;
		Point midPoint() const;
		void draw(Renderer renderer);
		void setColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha);
};

Line operator*(const double& num, const Line& line);
Line operator/(const double& num, const Line& line);
std::ostream& operator<<(std::ostream& output, const Line& line);
#endif
