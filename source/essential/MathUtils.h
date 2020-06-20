#ifndef MATH_UTILS_H
#define MATH_UTILS_H
#include "../primitives/Point.h"

namespace Math {
	Point bezier2ndDegreeDerivative(Point start, Point end, Point control, double t);
}
#endif
