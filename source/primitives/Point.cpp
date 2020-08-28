#include "Point.h"

Point::Point() : x(0.0 / 0.0), y(0.0 / 0.0) {}

Point::Point(const double& x, const double& y) : x(x), y(y) {}

Point::~Point() {}

Point::Point(const Point& point) : x(point.x), y(point.y) {}

Point::Point(const Point* point) : x(point->x), y(point->y) {}

double Point::originDistance() const {
	return this->distanceToPoint(0, 0);
}

Point Point::operator-() const {
	return *this * -1;
}

Point Point::operator-(const Point& point) const {
	return Point(this->x - point.x, this->y - point.y);
}

Point Point::operator+(const Point& point) const {
	return Point(this->x + point.x, this->y + point.y);
}

void Point::operator-=(const Point& delta) {
	*this += delta.negate();
}

void Point::operator+=(const Point& delta) {
	this->x += delta.x;
	this->y += delta.y;
}

Point& Point::operator=(const Point& point) {
	if (this != &point){
		x = point.x;
		y = point.y;
	}
	return *this;
}

Point Point::rotate90() const {
	return Point(this->y, -this->x);
}

Point Point::toInt() const {
	return Point(int(this->x), int(this->y));
}

std::ostream& operator<<(std::ostream &output, const Point &point) {
	output << "(" << double(point.x) << ", " << double(point.y) << ")";
	return output;
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

Point Point::getUnitVector() const {
	if (this->getMagnitude() < 0.0001) return Point(0, 0);
	return (*this) / this->getMagnitude();
}

double Point::getAngle() const {
	return atan2(this->y, this->x);
}

bool Point::isNull() const {
	return this->x != this->x && this->y != this->y;
}

bool Point::isZero() const {
	return !this->getNonZero();
}

bool Point::isReal() const {
	return !isNull();
}

Point Point::copy() const {
	return Point(this->x, this->y);
}

void Point::xZero() {
	this->x = 0;
}

void Point::yZero() {
	this->y = 0;
}

inline double Point::getMagnitude() const {
	return sqrt(this->getFastMagnitude());
}

inline double Point::getFastMagnitude() const {
	return pow(this->x, 2) + pow(this->y, 2);
}

bool Point::getNonZero() const {
	return ((std::abs(this->x) > ROUNDING || std::abs(this->y) > ROUNDING) 
			&& (this->x == this->x && this->y == this->y)); // This part is too make sure it isn't nan
}

bool Point::operator==(const Point& point) const {
	return (std::abs(point.x - this->x) < ROUNDING) && (std::abs(point.y - this->y) < ROUNDING);
}

bool Point::operator!=(const Point& point) const {
	return !(*this == point);
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

Point Point::operator/(const double& num) const {
	return Point(this->x / num, this->y / num);
}

Point Point::operator*(const double& num) const {
 	return Point(this->x * num, this->y * num);
}

void Point::zero() {
	this->x = 0;
	this->y = 0;
}

double Point::operator*(const Point& other) const {
	// Dot product
	return (this->x * other.x) + (this->y * other.y);
}

void Point::operator*=(const double& num) {
	this->x *= num;
	this->y *= num;
}

void Point::operator/=(const double& num) {
	this->x /= num;
	this->y /= num;
}

Point operator*(const double& other, const Point& point) {
	return point * other;
}
