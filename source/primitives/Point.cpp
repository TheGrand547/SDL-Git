#include "Point.h"

Point::Point(float xCoordinate, float yCoordinate) {
	xval = xCoordinate;
	yval = yCoordinate;
}

Point::~Point() {}

Point::Point(const Point &point) {
	this->xval = point.xval;
	this->yval = point.yval;
}
Point::Point(const Point *point) {
	xval = point->xval;
	yval = point->yval;
}

float Point::x() const {
	return this->xval;
}

float Point::y() const {
	return this->yval;
}

float Point::originDistance() const {
	return this->distanceToPoint(0, 0);
}

Point Point::operator-(const Point& point) const {
	return Point(this->xval - point.xval, this->yval - point.yval);
}

Point Point::operator+(const Point& point) const {
	return Point(this->xval + point.xval, this->yval + point.yval);
}

void Point::operator-=(const Point& delta) {
	*this += delta.negate();
}

void Point::operator+=(const Point& delta) {
	this->xval += delta.xval;
	this->yval += delta.yval;
}

Point& Point::operator=(const Point& that) {
	xval = that.xval;
	yval = that.yval;
	return *this;
}

Point Point::toInt() const {
	return Point(int(this->xval), int(this->yval));
}

std::ostream& operator<<(std::ostream &output, const Point &point) {
	output << "(" << float(point.x()) << ", " << float(point.y()) << ")";
	return output;
}

float Point::distanceToPoint(const Point& point) const {
	float dx = this->xval - point.x();
	float dy = this->yval - point.y();
	return sqrt(dx*dx + dy*dy);
}

float Point::distanceToPoint(float x, float y) const {
	return this->distanceToPoint(Point(x, y));
}

Point Point::getUnitVector() const {
	if (this->getMagnitude() < 0.0001) {
		return Point(0, 0);
	}
	return (*this) / this->getMagnitude();
}

float Point::getAngle() const {
	return atan2(this->yval, this->xval);
}

bool Point::isNull() const {
	if (this->xval != this->xval && this->yval != this->yval) {
		return true;
	}
	return false;
}

bool Point::isZero() const {
	return !this->getNonZero();
}

bool Point::isReal() const {
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

float Point::getMagnitude() const {
	return sqrt(pow(this->xval, 2) + pow(this->yval, 2));
}

bool Point::getNonZero() const {
	return ((std::abs(this->xval) > .0001 || std::abs(this->yval) > .0001) && (this->xval == this->xval || this->yval == this->yval)); // TODO: Define accuarcy constant
}

bool Point::operator==(const Point& point) {
	return std::abs(point.xval - this->xval) < 0.000001 && std::abs(point.yval - this->yval) < 0.000001;
}

bool Point::operator!=(const Point& point) {
	return !(*this == point);
}

Point Point::negate() const {
	return Point(-this->xval,-this->yval);
}

Point Point::onlyX() const {
	return Point(this->xval, 0);
}

Point Point::onlyY() const {
	return Point(0, this->yval);
}

Point Point::operator/(const float& num) const {
	return Point(this->xval / num, this->yval / num);
}

Point Point::operator*(const float& num) const {
	return Point(this->xval * num, this->yval * num);
}

void Point::zero() {
	this->xval = 0;
	this->yval = 0;
}

float Point::operator*(const Point& other) const {
	return (this->xval * other.xval) + (this->yval * other.yval);
}
