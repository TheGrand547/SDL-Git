#include "PointDelta.h"
#include "primatives/Point.h"

PointDelta::~PointDelta() {}

PointDelta::PointDelta() : Point(0, 0) {
	this->xmin = 0;
	this->ymin = 0;
}

PointDelta::PointDelta(float xval, float yval, float xMin, float yMin) : Point(xval, yval) {
	this->xmin = xMin;
	this->ymin = yMin;
}

PointDelta::PointDelta(Point point, float xMin, float yMin) : Point(point) {
	this->xmin = xMin;
	this->ymin = yMin;
}

PointDelta::PointDelta(const PointDelta &that) : Point(that){
	this->xmin = that.xmin;
	this->ymin = that.ymin;
}

float PointDelta::calcAngle(Point point) {
	if(point.y() != 0 || point.x() != 0)
		 return atan2(0-point.y(), point.x());
	return 0;
}

void PointDelta::reduceToBounds() {			
	if (this->getMagnitude() > this->getMaxMagnitude()) {
		float tempFloat = calcAngle(*this);
		this->xval = this->getXMin() * cos(tempFloat);
		this->yval = -this->getYMin() * sin(tempFloat);
	}
}

float PointDelta::getMaxMagnitude() {
	return sqrt((pow(this->xmin, 2) + pow(this->ymin, 2)));
}

float PointDelta::getXMin() {
	return this->xmin;
}

float PointDelta::getYMin() {
	return this->ymin;
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
	this->xmin = that.xmin;
	this->ymin = that.ymin;
	return *this;
}

PointDelta PointDelta::operator/(const float &num) {
	return PointDelta(this->xval / num, this->yval / num, this->xmin, this->ymin);
}

PointDelta PointDelta::operator*(const float &num) {
	return PointDelta(this->xval * num, this->yval * num, this->xmin * num, this->ymin * num);
}

void PointDelta::setBounds(float xMax, float yMax) {
	this->xmin = xMax;
	this->ymin = yMax;
	this->reduceToBounds();
}

PointDelta PointDelta::onlyX() {
	return PointDelta(this->xval, 0, this->xmin, this->ymin);
}

PointDelta PointDelta::onlyY() {
	return PointDelta(0, this->yval, this->xmin, this->ymin);
}

Point PointDelta::getXPoint() {
	return Point(this->xmin, 0);
}

Point PointDelta::getYPoint() {
	return Point(0, this->ymin);
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
