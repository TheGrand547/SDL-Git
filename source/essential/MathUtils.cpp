#include "MathUtils.h"

// TODO: Potentially rename this file
// TODO: Add more math
double Math::gauss(double x, double sigma) { // Taken from https://github.com/anlcnydn/bilateral/blob/master/bilateral_filter.cpp
    return exp(-(pow(x, 2)) / (2 * pow(sigma, 2))) / (2 * M_PI * pow(sigma, 2));
}

double Math::angleBetween(const Point& origin, const Point& end) {
	return atan2(end.y - origin.y, origin.x - end.x);
}

Point Math::bezier2ndDegreeDerivative(Point start, Point end, Point control, double t) {
	return (control - start) * 2 * (1 - t) + (end - control) * 2 * t;
}
