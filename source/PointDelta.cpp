#include "PointDelta.h"
#include "primitives/Point.h"

PointDelta::~PointDelta() {}

PointDelta::PointDelta() : Point(0, 0) {
	this->magnitude = 0;
}

PointDelta::PointDelta(float xval, float yval, float magnitude) : Point(xval, yval) {
	this->magnitude = magnitude;
}

PointDelta::PointDelta(Point point, float magnitude) : Point(point) {
	this->magnitude = magnitude;
}

PointDelta::PointDelta(const PointDelta &that) : Point(that){
	this->magnitude = that.magnitude;
}

float PointDelta::calcAngle(Point point) {
	if(point.y() != 0 || point.x() != 0) {
		 return atan2(0-point.y(), point.x());
	 }
	return 0;
}

void PointDelta::reduceToBounds() {			
	if (this->getMagnitude() > this->magnitude) {
		float tempFloat = calcAngle(*this);
		this->xval = this->magnitude * cos(tempFloat);
		this->yval = -this->magnitude * sin(tempFloat);
	}
}

float PointDelta::getMagnitude() {
	return sqrt((pow(this->xval, 2) + pow(this->yval, 2)));
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
	this->xval = that.xval;
	this->yval = that.yval;
	this->magnitude = that.magnitude;
	return *this;
}

PointDelta PointDelta::operator/(const float &num) {
	return PointDelta(this->xval / num, this->yval / num, this->magnitude);
}

PointDelta PointDelta::operator*(const float &num) {
	return PointDelta(this->xval * num, this->yval * num, this->magnitude * num);
}

void PointDelta::setMagnitude(float magnitude) {
	this->magnitude = magnitude;
	this->reduceToBounds();
}

PointDelta PointDelta::onlyX() {
	return PointDelta(this->xval, 0, this->magnitude);
}

PointDelta PointDelta::onlyY() {
	return PointDelta(0, this->yval, this->magnitude);
}

Point PointDelta::getXPoint() {
	return Point(this->magnitude, 0);
}

Point PointDelta::getYPoint() {
	return Point(0, this->magnitude);
}

bool PointDelta::operator>(const int &val) {
	if (this->xval > val || this->yval > val) {
		return true;
	}
	return false;
}

bool PointDelta::operator<(const int &val) {
	if (this->xval < val || this->yval < val) {
		return true;
	}
	return false;
}

PointDelta PointDelta::negate() {
	return PointDelta(-this->xval, -this->yval, this->magnitude);
}
