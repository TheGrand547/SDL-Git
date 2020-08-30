#pragma once
#ifndef POINT_H
#define POINT_H
#include "../essential/random.h"
#include<math.h>
#include<iostream>
#include <cassert>

struct Point {
	double x, y;
	Point();
	Point(const double& x, const double& y = 0);
	Point(const Point& point);
	~Point();
	Point operator-() const;
	Point operator+(const Point& point) const;
	Point operator-(const Point& point) const;
	Point operator+(const double& num) = delete;
	Point operator-(const double& num) = delete;
	Point& operator=(const Point& point);
	Point operator/(const double& num) const;
	Point operator*(const double& num) const;
	Point copy() const;
	Point getUnitVector() const;
	Point negate() const;
	Point onlyX() const;
	Point onlyY() const;
	Point rotate90() const;
	Point toInt() const;
	bool getNonZero() const;
	bool isZero() const;
	bool isNull() const;
	bool isReal() const;
	bool operator==(const Point& point) const;
	bool operator!=(const Point& point) const;
	double distanceToPoint(const Point& point = Point(0, 0)) const;
	double distanceToPoint(const double& x, const double& y) const;
	double fastDistanceToPoint(const Point& point = Point(0, 0)) const;
	double getAngle() const;
	double getMagnitude() const;
	double getFastMagnitude() const;
	double operator*(const Point& other) const;
	double originDistance() const;
	friend std::ostream& operator<<(std::ostream &output, const Point& point);
	void operator+=(const Point& delta);
	void operator-=(const Point& delta);
	void operator+=(const double& num) = delete;
	void operator-=(const double& num) = delete;
	void operator*=(const double& num);
	void operator/=(const double& num);
	void xZero();
	void yZero();
	void zero();
};

Point operator*(const double& other, const Point& point);
Point operator+(const double& num, const Point& point) = delete;
Point operator-(const double& num, const Point& point) = delete;
Point operator/(const double& num, const Point& point) = delete;
#endif
