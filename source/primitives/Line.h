#pragma once
#ifndef LINE_H
#define LINE_H
#include<cmath>
#include<SDL2/SDL.h>
#include<SDL2/SDL2_gfxPrimitives.h>
#include <cassert>
#include "Point.h"
#include "../Color.h"
#include "../essential/random.h"
#include "../essential/util.h"

typedef Uint8 uint8_t;

class Line: public Color {
	// Represents a line segment in the form, ax+by=c, bounded by the points A and B
	private:
		Point originPoint, endingPoint;
	public:	
		Line(Point pointA = Point(), Point pointB = Point(), uint8_t r = 0x00, uint8_t g = 0x00, uint8_t b = 0xFF, uint8_t a = 0xFF);
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
		friend std::ostream& operator<<(std::ostream& output, const Line& line);
		void drawLine(SDL_Renderer* renderer, Point offset = Point(0, 0));
		void setColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha);
};

Line operator*(const double& num, const Line& line);
Line operator/(const double& num, const Line& line);
#endif
