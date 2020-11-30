#pragma once
#ifndef MATH_UTILS_H
#define MATH_UTILS_H
#include "../primitives/Point.h"
#include <math.h>

namespace Math {
	inline double radians(const double& degrees);
	inline double degrees(const double& radians);
	double angleBetween(const Point& origin, const Point& end);
	double gauss(const double& x, const double& sigma);
	Point bezier2ndDegreeDerivative(const Point& start, const Point& end, const Point& control, const double& t);
}

inline double Math::radians(const double& degrees) {
	return degrees * (M_PI / 180.0);
}

inline double Math::degrees(const double& radians) {
	return radians * (180.0 / M_PI);
}
#endif
