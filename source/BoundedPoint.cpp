#include "BoundedPoint.h"

BoundedPoint::BoundedPoint() : Point(), xMax(0), yMax(0) {}

BoundedPoint::BoundedPoint(double xMax, double yMax) : Point(0, 0), xMax(xMax), yMax(yMax) {} 

BoundedPoint::BoundedPoint(double xpos, double ypos, double xMax, double yMax) : Point(xpos, ypos), xMax(xMax), yMax(yMax) {}

BoundedPoint::BoundedPoint(Point pos, double xMax, double yMax) : Point(pos), xMax(xMax), yMax(yMax) {}

BoundedPoint::BoundedPoint(const BoundedPoint& other) : Point(other.x, other.y), xMax(other.xMax), yMax(other.yMax) {}

BoundedPoint& BoundedPoint::operator=(const BoundedPoint& other){
	this->x = other.x;
	this->y = other.y;
	this->xMax = other.xMax;
	this->yMax = other.yMax;
	return *this;
}

BoundedPoint::~BoundedPoint() {}

void BoundedPoint::reduce() {
	this->x = (this->x <= 0) ? 0 : this->x;
	this->y = (this->y <= 0) ? 0 : this->y;
	this->x = (this->x >= this->xMax) ? this->xMax : this->x;
	this->y = (this->y >= this->yMax) ? this->yMax : this->y;
}

void BoundedPoint::operator+=(Point delta) {
	Point::operator+=(delta);
	this->reduce();
}

void BoundedPoint::operator-=(Point delta) {
	Point::operator-=(delta);
	this->reduce();
}

void BoundedPoint::maxX() {
	this->x = this->xMax;
}

void BoundedPoint::maxY() {
	this->y = this->yMax;
}
