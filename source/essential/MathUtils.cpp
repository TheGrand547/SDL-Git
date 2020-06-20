#include "MathUtils.h"

Point Math::bezier2ndDegreeDerivative(Point start, Point end, Point control, double t) {
	return (control - start) * 2 * (1 - t) + (end - control) * 2 * t;
}
