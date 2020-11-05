#pragma once
#ifndef POINT_H
#define POINT_H
#include <iostream>
// TODO: Add directional indicators <- what does this mean

struct Point {
	double x, y;
	Point();
	Point(const double& x, const double& y = 0);
	Point(const Point& point);
	~Point();
	bool getNonZero() const;
	bool isAbove(const Point& point) const;
	bool isBelow(const Point& point) const;
	bool isLeftOf(const Point& point) const;
	bool isNull() const;
	bool isReal() const;
	bool isRightOf(const Point& point) const;
	bool isZero() const;
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
	Point copy() const;
	Point getUnitVector() const;
	Point negate() const;
	Point onlyX() const;
	Point onlyY() const;
	Point operator-() const;
	Point operator+(const Point& point) const;
	Point operator-(const Point& point) const;
	Point operator+(const double& num) = delete;
	Point operator-(const double& num) = delete;
	Point operator/(const double& num) const;
	Point operator*(const double& num) const;
	Point& operator=(const Point& point);
	Point rotate90() const;
	Point toInt() const;
	void operator+=(const Point& delta);
	void operator-=(const Point& delta);
	void operator+=(const double& num) = delete;
	void operator-=(const double& num) = delete;
	void operator*=(const double& num);
	void operator/=(const double& num);
	void xZero();
	void yZero();
	void zero();

	static double angleFromVector(const Point& vector);
	static Point vectorFromAngle(const double& angle);
};

Point operator*(const double& other, const Point& point);
Point operator+(const double& num, const Point& point) = delete;
Point operator-(const double& num, const Point& point) = delete;
Point operator/(const double& num, const Point& point) = delete;
std::ostream& operator<<(std::ostream& output, const Point& point);

namespace std {
	template<> struct hash<Point> {
		std::size_t operator()(const Point& thing) const noexcept {
			return std::hash<double>{}(thing.x) ^ (std::hash<double>{}(thing.y) >> 5);
		}
	};
}
#endif
