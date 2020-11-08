#include "Point.h"
#include "../essential/misc.h"
#include <math.h>

Point::Point() : x(0.0 / 0.0), y(0.0 / 0.0) {}

Point::Point(const double& x, const double& y) : x(x), y(y) {}

Point::~Point() {}

Point::Point(const Point& point) : x(point.x), y(point.y) {}

bool Point::getNonZero() const {
	return ((!::isZero(this->x) || !::isZero(this->y)) 
		&& (this->x == this->x && this->y == this->y)); // This part is too make sure it isn't nan
}

bool Point::isAbove(const Point& point) const {
	if (point.isReal()) return this->y < point.y;
	return false;
}

bool Point::isBelow(const Point& point) const {
	if (point.isReal()) return !this->isAbove(point);
	return false;
}

bool Point::isLeftOf(const Point& point) const {
	if (point.isReal()) return this->x < point.y;
	return false;
}

bool Point::isNull() const {
	return this->x != this->x && this->y != this->y;
}

bool Point::isReal() const {
	return !isNull();
}

bool Point::isRightOf(const Point& point) const {
	if (point.isReal()) return !this->isLeftOf(point);
	return false;
}

bool Point::isZero() const {
	return !this->getNonZero();
}

bool Point::operator==(const Point& point) const {
	return ::isZero(point.x - this->x) && ::isZero(point.y - this->y);
}

bool Point::operator!=(const Point& point) const {
	return !(*this == point);
}

double Point::distanceToPoint(const Point& point) const {
	return sqrt(this->fastDistanceToPoint(point));
}

double Point::distanceToPoint(const double& x, const double& y) const {
	return this->distanceToPoint(Point(x, y));
}

double Point::fastDistanceToPoint(const Point& point) const {
	double dx = this->x - point.x;
	double dy = this->y - point.y;
	return dx * dx + dy * dy;
}

double Point::getAngle() const {
	return atan2(this->y, this->x);
}

double Point::getMagnitude() const {
	return sqrt(this->getFastMagnitude());
}

double Point::getFastMagnitude() const {
	return pow(this->x, 2) + pow(this->y, 2);
}

double Point::operator*(const Point& other) const {
	// Dot product
	return (this->x * other.x) + (this->y * other.y);
}

double Point::originDistance() const {
	return this->distanceToPoint(0, 0);
}

Point Point::copy() const {
	return Point(this->x, this->y);
}

Point Point::getUnitVector() const {
	double magnitude = this->getMagnitude();
	if (::isZero(magnitude)) return Point(0, 0);
	return (*this) / magnitude;
}

Point Point::negate() const {
	return Point(-this->x, -this->y);
}

Point Point::onlyX() const {
	return Point(this->x, 0);
}

Point Point::onlyY() const {
	return Point(0, this->y);
}

Point Point::operator-() const {
	return this->negate();
}

Point Point::operator-(const Point& point) const {
	return Point(this->x - point.x, this->y - point.y);
}

Point Point::operator+(const Point& point) const {
	return Point(this->x + point.x, this->y + point.y);
}

Point Point::operator/(const double& num) const {
	return Point(this->x / num, this->y / num);
}

Point Point::operator*(const double& num) const {
 	return Point(this->x * num, this->y * num);
}

Point& Point::operator=(const Point& point) {
	if (this != &point) {
		this->x = point.x;
		this->y = point.y;
	}
	return *this;
}

Point Point::rotate90() const {
	return Point(this->y, -this->x);
}

Point Point::toInt() const {
	return Point(int(this->x), int(this->y));
}

void Point::operator+=(const Point& delta) {
	this->x += delta.x;
	this->y += delta.y;
}

void Point::operator-=(const Point& delta) {
	*this += delta.negate();
}

void Point::operator*=(const double& num) {
	this->x *= num;
	this->y *= num;
}

void Point::operator/=(const double& num) {
	this->x /= num;
	this->y /= num;
}

void Point::xZero() {
	this->x = 0;
}

void Point::yZero() {
	this->y = 0;
}

void Point::zero() {
	this->x = 0;
	this->y = 0;
}

// ------------------------------------------------
// --------- Related Non-class Methods ------------
// ------------------------------------------------

Point operator*(const double& other, const Point& point) {
	return point * other;
}

std::ostream& operator<<(std::ostream& output, const Point &point) {
	output << "(" << double(point.x) << ", " << double(point.y) << ")";
	return output;
}

double Point::angleFromVector(const Point& vector) {
	return atan2(-vector.y, vector.x);
}

Point Point::vectorFromAngle(const double& angle) {
	return {cos(angle), sin(angle)};
}
