#include "Triangle.h"

Triangle::Triangle() : a(0, 0), b(0, 0), c(0, 0) {}

Triangle::Triangle(Point a, Point b, Point c) : a(a), b(b), c(c) {}

Triangle::~Triangle() {}

bool Triangle::isReal() const {
	return this->a.getNonZero() || this->b.getNonZero() || this->c.getNonZero();
}

double Triangle::getArea() const {
	return std::abs((this->a.x * (this->b.y - this->c.y) + this->b.x * (this->c.y - this->a.y) + this->c.x * (this->a.y - this->b.y)) / 2.0);
}

int Triangle::numLines() const {
	return 3;
}

int Triangle::numPoints() const {
	return 3;
}

Point Triangle::getCenter() const {
	return (this->a + this->b + this->c) / 3.0;
}

std::vector<Line> Triangle::getLines() const {
	return {Line(this->a, this->b), Line(this->b, this->c), Line(this->a, this->c)};
}

std::vector<Point> Triangle::getPoints() const {
	return {this->a, this->b, this->c};
}

