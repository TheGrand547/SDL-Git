#include "Point.h"

inline Point::Point(float xCoordinate, float yCoordinate) {
	xval = xCoordinate;
	yval = yCoordinate;
}

inline Point::~Point() {}

inline Point::Point(const Point &point) {
	this->xval = point.xval;
	this->yval = point.yval;
}
inline Point::Point(const Point *point) {
	xval = point->xval;
	yval = point->yval;
}

inline float Point::x() const {
	return this->xval;
}

inline float Point::y() const {
	return this->yval;
}

inline float Point::originDistance() {
	return distanceToPoint(0,0);
}

inline Point Point::operator-(const Point &point) {
	return Point(this->xval - point.xval, this->yval - point.yval);
}

inline Point Point::operator+(const Point &point) {
	return Point(this->xval + point.xval, this->yval + point.yval);
}

void Point::operator-=(Point delta) {
	*this += delta.negate();
}

void Point::operator+=(Point delta) {
	this->xval += delta.xval;
	this->yval += delta.yval;
}

inline Point& Point::operator=(const Point &that) {
	xval = that.xval;
	yval = that.yval;
	return *this;
}

inline std::ostream& operator<<(std::ostream &output, const Point &point) {
	output << "(" << float(point.x()) << ", " << float(point.y()) << ")";
	return output;
}

float Point::distanceToPoint(Point point) {
	float dx = this->xval - point.x();
	float dy = this->yval - point.y();
	return sqrt(dx*dx + dy*dy);
}

inline float Point::distanceToPoint(float x, float y) {
	return this->distanceToPoint(Point(x, y));
}

bool Point::isNull() {
	if (this->xval == -1 && this->yval == -1) {
		return true;
	}
	return false;
}

bool Point::isReal() {
	return !isNull();
}

Point Point::copy() const {
	return Point(this->xval, this->yval);
}

void Point::xZero() {
	this->xval = 0;
}

void Point::yZero() {
	this->yval = 0;
}

inline float Point::getMagnitude() {
	return sqrt(pow(this->xval, 2) + pow(this->yval, 2));
}

bool Point::getNonZero() {
	return (int(this->xval) != 0 || int(this->yval) != 0);
}

inline Point Point::negate() {
	return Point(-this->xval,-this->yval);
}

Point Point::onlyX() {
	return Point(this->xval, 0);
}

Point Point::onlyY() {
	return Point(0, this->yval);
}

Point Point::operator/(const float &num) {
	return Point(this->xval / num, this->yval / num);
}
