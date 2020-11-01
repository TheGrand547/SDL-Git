#include "MathUtils.h"

// TODO: Potentially rename this file
// TODO: Add more math

// TODO: Rename this to just guass(x, sigma), function is implied
double Math::gaussian(double x, double sigma) { // Taken from https://github.com/anlcnydn/bilateral/blob/master/bilateral_filter.cpp
    return exp(-(pow(x, 2)) / (2 * pow(sigma, 2))) / (2 * M_PI * pow(sigma, 2));
}

Point Math::bezier2ndDegreeDerivative(Point start, Point end, Point control, double t) {
	return (control - start) * 2 * (1 - t) + (end - control) * 2 * t;
}

