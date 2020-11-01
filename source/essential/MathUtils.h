#pragma once
#ifndef MATH_UTILS_H
#define MATH_UTILS_H
#include "../primitives/Point.h"
#include <math.h>

namespace Math {
	double gaussian(double x, double sigma);
	Point bezier2ndDegreeDerivative(Point start, Point end, Point control, double t);
}
#endif
