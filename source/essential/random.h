#pragma once
#include<math.h>
/* Misc functions with no dependencies */

template<class T>
float radians(T degrees) {
	return degrees * (M_PI / 180.0);
}

template<class T>
void mMax(T numA, T numB, T &iMin, T &iMax) {
	iMin = (numA > numB) ? numB : numA;
	iMax = (numA > numB) ? numA : numB;
}

template<class T>
bool valueInRange(T value, T min, T max){ 
	return (int(value) >= int(min)) && (int(value) <= int(max)); 
}

template<class T>
bool thresholdValueInRange(T value, T min, T max){ 
	return ((int(value) >= int(min) - 2) && (int(value) <= int(max) + 2)); 
}

template<class T>
bool thresholdValueInRange(T value, T *min, T *max){ 
	return thresholdValueInRange(int(value), int(*min), int(*max));
}
