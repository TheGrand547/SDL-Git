#pragma once
#ifndef POINT_H
#define POINT_H
#include<math.h>
#include<iostream>

class Point {
	protected:
		float xval, yval;
	public:
		Point(float xCoordinate = 0.0 / 0.0, float yCoordinate = 0.0 / 0.0);
		Point(const Point &point);
		Point(const Point *point);
		~Point();
		Point operator-(const Point &point);
		Point operator+(const Point &point);
		Point& operator=(const Point &that);
		Point operator/(const float &num) const;
		Point operator*(const float &num) const;
		Point copy() const;
		Point negate() const;
		Point onlyX() const;
		Point onlyY() const;
		Point toInt() const;
		Point getUnitVector() const;
		bool getNonZero() const;
		bool isZero() const;
		bool isNull() const;
		bool isReal() const;
		bool operator==(const Point& point);
		bool operator!=(const Point& point);
		float distanceToPoint(Point point) const;
		float distanceToPoint(float x, float y) const;
		float getMagnitude() const;
		float originDistance() const;
		float x() const;
		float y() const;
		friend std::ostream &operator<<(std::ostream &output, const Point &point);
		void operator+=(Point delta);
		void operator-=(Point delta);
		void xZero();
		void yZero();
		void zero();
};
#endif
