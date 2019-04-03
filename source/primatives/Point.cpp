#include "Point.h"

Point::Point(float xCoordinate, float yCoordinate) {
	xval = new float(xCoordinate);
	yval = new float(yCoordinate);
}

Point::~Point() {
	delete this->xval;
	delete this->yval;
}

Point::Point(const Point &point) {
	this->xval = new float(*point.xval);
	this->yval = new float(*point.yval);
}
Point::Point(const Point *point) {
	xval = new float(*(point->xval));
	yval = new float(*(point->yval));
}

float Point::x() const {
	return *xval;
}

float Point::y() const {
	return *yval;
}

float Point::originDistance() {
	return distanceToPoint(0,0);
}

Point Point::operator-(const Point &point) {
	Point temp;
	(temp.xval) = new float( *(this->xval) - *(point.xval));
	(temp.yval) = new float (*(this->yval) - *(point.yval));
	return temp;
}
Point Point::operator+(const Point &point) {
	Point temp;
	(temp.xval) = new float(*(this->xval) + *(point.xval));
	(temp.yval) = new float(*(this->yval) + *(point.yval));
	return temp;
}

void Point::operator-=(Point delta) {
	*(this->xval) -= delta.x();
	*(this->yval) -= delta.y();
}

void Point::operator+=(Point delta) {
	*(this->xval) += delta.x();
	*(this->yval) += delta.y();
}

Point& Point::operator=(const Point &that) {
	*xval = that.x();
	*yval = that.y();
	return *this;
}

std::ostream& operator<<(std::ostream &output, const Point &point) {
	output << "(" << int(point.x()) << ", " << int(point.y()) << ")";
	return output;
}

float Point::distanceToPoint(Point point) {
	float dx = *xval - point.x();
	float dy = *yval - point.y();
	return sqrt(dx*dx + dy*dy);
}

float Point::distanceToPoint(float x, float y) {
	float dx = *xval - x;
	float dy = *yval - y;
	return sqrt(dx * dx + dy * dy);
}

bool Point::isNull() {
	if (*xval == -1 && *yval == -1)
		return true;
	return false;
}

bool Point::isReal() {
	return !isNull();
}

Point Point::copy() const {
	return Point(*(this->xval),*(this->yval));
}
void Point::xZero() {
	*xval = 0;
}
void Point::yZero() {
	*yval = 0;
}

float Point::getMagnitude() {
	return sqrt(pow(*xval, 2) + pow(*yval, 2));
}

bool Point::getNonZero() {
	return (*this->xval != 0 || *this->yval != 0);
}
