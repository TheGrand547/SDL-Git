#include "misc.h"

double gaussian(double x, double sigma) { // Taken from https://github.com/anlcnydn/bilateral/blob/master/bilateral_filter.cpp
    return exp(-(pow(x, 2)) / (2 * pow(sigma, 2))) / (2 * M_PI * pow(sigma, 2));
}

bool valueInRange(double value, double min, double max) {
	return (value > min && value < max) || (std::abs(value - min) < ROUNDING) || (std::abs(value - max) < ROUNDING); 
}
