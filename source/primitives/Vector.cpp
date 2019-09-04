#include "Vector.h"

Vector::Vector(float angle) : Point(cos(angle), sin(angle)) {}

Vector::Vector(float x, float y) : Point(x, y) {}

Vector::~Vector() {}

Vector Vector::operator*(const double& num) {
	return Vector(this->xval * num, this->yval * num);
}

Vector Vector::operator/(const double& num) {
	return (*this) * (1.0 / num);
}

float Vector::dot(const Vector other) {
	return (this->xval * other.xval) + (this->yval * other.yval);
}

float Vector::operator*(const Vector& other) {
	return this->dot(other);
}

float Vector::magnitude() const {
	return sqrt(pow(this->xval, 2) + pow(this->yval, 2));
}

float Vector::angleBetween(const Vector other) {
	return acos(this->dot(other) / (this->magnitude() * other.magnitude()));
}

Vector operator*(const double& num, Vector& other) {
	return other * num;
}
