#include "misc.h"

bool isZero(const double& num) {
	return std::abs(num) < ROUNDING;
}

bool valueInRange(double value, double min, double max) {
	return (value > min && value < max) || (std::abs(value - min) < ROUNDING) || (std::abs(value - max) < ROUNDING); 
}
