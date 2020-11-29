#include "misc.h"

bool valueInRange(const double& value, const double& min, const double& max) {
	return (value > min && value < max) || (std::abs(value - min) < ROUNDING) || (std::abs(value - max) < ROUNDING); 
}
