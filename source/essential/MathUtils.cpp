#include "MathUtils.h"

// TODO: Potentially rename this file
// TODO: Add more math

// TODO: This feels really fucking wrong for some reason
double Math::angleBetween(const Point& origin, const Point& end) {
	return atan2(end.y - origin.y, end.x - origin.x);
}

double Math::gauss(const double& x, const double& sigma) { // Taken from https://github.com/anlcnydn/bilateral/blob/master/bilateral_filter.cpp
    return exp(-(pow(x, 2)) / (2 * pow(sigma, 2))) / (2 * M_PI * pow(sigma, 2));
}

Point Math::bezier2ndDegreeDerivative(const Point& start, const Point& end, const Point& control, const double& t) {
	return (control - start) * 2 * (1 - t) + (end - control) * 2 * t;
}
