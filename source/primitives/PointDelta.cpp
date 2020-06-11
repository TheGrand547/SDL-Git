#include "PointDelta.h"
#include "Point.h"

PointDelta::~PointDelta() {}

PointDelta::PointDelta() : Point(0, 0) {
	this->magnitude = 0;
}

PointDelta::PointDelta(double xval, double yval, double magnitude) : Point(xval, yval) {
	this->magnitude = magnitude;
	this->reduceToBounds();
}

PointDelta::PointDelta(Point point, double magnitude) : Point(point) {
	this->magnitude = magnitude;
	this->reduceToBounds();
}

PointDelta::PointDelta(const PointDelta &that) : Point(that){
	this->magnitude = that.magnitude;
	this->reduceToBounds();
}

double PointDelta::calcAngle(Point point) {
	if(point.y != 0 || point.x != 0) {
		 return atan2(-point.y, point.x);
	}
	return 0;
}

void PointDelta::reduceToBounds() {			
	if (this->getMagnitude() > this->magnitude) {
		double tempFloat = calcAngle(*this);
		this->x = this->magnitude * cos(tempFloat);
		this->y = -this->magnitude * sin(tempFloat);
	}
}

double PointDelta::getMagnitude() {
	return sqrt((pow(this->x, 2) + pow(this->y, 2)));
}

void PointDelta::operator-=(Point delta) {
	Point::operator-=(delta);
	reduceToBounds();
}

void PointDelta::operator+=(Point delta) {
	Point::operator+=(delta);
	reduceToBounds();
}

PointDelta& PointDelta::operator=(const PointDelta &that) {
	this->x = that.x;
	this->y = that.y;
	this->magnitude = that.magnitude;
	return *this;
}

PointDelta PointDelta::operator/(const double &num) {
	return PointDelta(this->x / num, this->y / num, this->magnitude);
}

PointDelta PointDelta::operator*(const double &num) {
	return PointDelta(this->x * num, this->y * num, this->magnitude * num);
}

void PointDelta::setMagnitude(double magnitude) {
	this->magnitude = magnitude;
	this->reduceToBounds();
}

PointDelta PointDelta::onlyX() {
	return PointDelta(this->x, 0, this->magnitude);
}

PointDelta PointDelta::onlyY() {
	return PointDelta(0, this->y, this->magnitude);
}

Point PointDelta::getXPoint() {
	return Point(this->magnitude, 0);
}

Point PointDelta::getYPoint() {
	return Point(0, this->magnitude);
}

bool PointDelta::operator>(const int &val) {
	return this->x > val || this->y > val;
}

bool PointDelta::operator<(const int &val) {
	return this->x < val || this->y < val;
}

PointDelta PointDelta::negate() {
	return PointDelta(-this->x, -this->y, this->magnitude);
}
