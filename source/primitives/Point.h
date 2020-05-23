#pragma once
#ifndef POINT_H
#define POINT_H
#include<math.h>
#include<iostream>

class Point {
	public:
		double xval, yval;
		
		Point(double xCoordinate = 0.0 / 0.0, double yCoordinate = 0.0 / 0.0);
		Point(const Point& point);
		Point(const Point* point);
		~Point();
		Point operator-(const Point& point) const;
		Point operator+(const Point& point) const;
		Point& operator=(const Point& that);
		Point operator/(const double& num) const;
		Point operator*(const double& num) const;
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
		bool operator==(const Point& point) const;
		bool operator!=(const Point& point) const;
		double distanceToPoint(const Point& point = Point(0, 0)) const;
		double distanceToPoint(double x, double y) const;
		double getAngle() const;
		double getMagnitude() const;
		double operator*(const Point& other) const;
		double originDistance() const;
		double x() const;
		double y() const;
		friend std::ostream &operator<<(std::ostream &output, const Point &point);
		void operator+=(const Point& delta);
		void operator-=(const Point& delta);
		void operator*=(const double& val);
		void operator/=(const double& val);
		void xZero();
		void yZero();
		void zero();
};
#endif
