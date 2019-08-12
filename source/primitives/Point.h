#pragma once
#ifndef POINT_H
#define POINT_H
#include<math.h>
#include<iostream>

class Point {
	protected:
		float xval, yval;
	public:
		Point(float xCoordinate=-1, float yCoordinate=-1);
		Point(const Point &point);
		Point(const Point *point);
		~Point();
		Point operator-(const Point &point);
		Point operator+(const Point &point);
		Point& operator=(const Point &that);
		Point operator/(const float &num);
		Point operator*(const float &num);
		Point copy() const;
		Point negate() const;
		Point onlyX();
		Point onlyY();
		bool getNonZero();
		bool isNull();
		bool isReal();
		float distanceToPoint(Point point);
		float distanceToPoint(float x, float y);
		float getMagnitude();
		float originDistance();
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
