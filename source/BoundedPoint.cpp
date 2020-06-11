#include "BoundedPoint.h"

BoundedPoint::BoundedPoint() : Point() {
	this->xMin = 0;
	this->xMax = 0;
	this->yMin = 0;
	this->yMax = 0;
}

BoundedPoint::BoundedPoint(float xMax, float yMax) : Point(0, 0) {
	this->xMin = 0;
	this->xMax = xMax;
	this->yMin = 0;
	this->yMax = yMax;
} 

BoundedPoint::BoundedPoint(float xpos, float ypos, float xMin, float yMin, float xMax, float yMax) : Point(xpos, ypos) {
	this->xMin = xMin;
	this->xMax = xMax;
	this->yMin = yMin;
	this->yMax = yMax;
}

BoundedPoint::BoundedPoint(Point pos, float xMin, float yMin, float xMax, float yMax) : Point(pos) {
	this->xMin = xMin;
	this->xMax = xMax;
	this->yMin = yMin;
	this->yMax = yMax;
}

BoundedPoint::BoundedPoint(const BoundedPoint &other) : Point(other.x, other.y){
	this->xMin = other.xMin;
	this->xMax = other.xMax;
	this->yMin = other.yMin;
	this->yMax = other.yMax;
}

BoundedPoint& BoundedPoint::operator=(BoundedPoint other){
	this->x = other.x;
	this->y = other.y;
	this->xMin = other.xMin;
	this->xMax = other.xMax;
	this->yMin = other.yMin;
	this->yMax = other.yMax;
	return *this;
}

BoundedPoint::~BoundedPoint() {}

void BoundedPoint::reduce() {
	this->x = (this->x <= this->xMin) ? this->xMin : this->x;
	this->x = (this->x >= this->xMax) ? this->xMax : this->x;
	this->y = (this->y <= this->yMin) ? this->yMin : this->y;
	this->y = (this->y >= this->yMax) ? this->yMax : this->y;
}

void BoundedPoint::operator+=(Point delta) {
	Point::operator+=(delta);
	reduce();
}

void BoundedPoint::operator-=(Point delta) {
	Point::operator-=(delta);
	reduce();
}

void BoundedPoint::zeroX() {
	this->x = 0;
}

void BoundedPoint::zeroY() {
	this->y = 0;
}

void BoundedPoint::maxX() {
	this->x = this->xMax;
}

void BoundedPoint::maxY() {
	this->y = this->yMax;
}
