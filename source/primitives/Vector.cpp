#include "Vector.h"

Vector::Vector(double angle) : Point(cos(angle), sin(angle)) {}

Vector::Vector(double x, double y) : Point(x, y) {}

Vector::~Vector() {}

Vector Vector::operator*(const double& num) {
	return Vector(this->xval * num, this->yval * num);
}

Vector Vector::operator/(const double& num) {
	return (*this) * (1.0 / num);
}

double Vector::dot(const Vector other) {
	return (this->xval * other.xval) + (this->yval * other.yval);
}

double Vector::operator*(const Vector& other) {
	return this->dot(other);
}

double Vector::magnitude() const {
	return sqrt(pow(this->xval, 2) + pow(this->yval, 2));
}

double Vector::angleBetween(const Vector other) {
	return acos(this->dot(other) / (this->magnitude() * other.magnitude()));
}

Vector operator*(const double& num, Vector& other) {
	return other * num;
}
