#include "random.h"

double gaussian(float x, double sigma) { // Taken from https://github.com/anlcnydn/bilateral/blob/master/bilateral_filter.cpp
    return exp(-(pow(x, 2))/(2 * pow(sigma, 2))) / (2 * M_PI * pow(sigma, 2));
}
