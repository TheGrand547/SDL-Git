#pragma once
#include<algorithm>
#include<cmath>
#include<math.h>
#include<stdlib.h>
#include<memory>
#include<utility>
#include<vector>
/* Misc functions with no dependencies */

template<class T>
float radians(T degrees) {
	return degrees * (M_PI / 180.0);
}

template<class T>
void mMax(T numA, T numB, T& iMin, T& iMax) {
	iMin = (numA > numB) ? numB : numA;
	iMax = (numA > numB) ? numA : numB;
}

bool valueInRange(double value, double min, double max);

template<class T>
bool valueInModRange(T value, T min, T max){ 
	return ((int(value) >= int(min) - 2) && (int(value) <= int(max) + 2)); 
}

template<class T>
T toTicks(T seconds) {
	return seconds * 1000.f;
}

template<class T>
T& choice(const std::vector<T>& vector) {
	return vector[rand() % vector.size()];
}

template<class T>
bool valueInVector(const std::vector<T>& vector, const T& element) {
	return std::find(vector.begin(), vector.end(), element) != vector.end();
}

template<class T>
bool valueNotInVector(const std::vector<T>& vector, const T& element) {
	return std::find(vector.begin(), vector.end(), element) == vector.end();
}
	
double gaussian(double x, double sigma);

template<class T>
bool shareNoElements(std::pair<std::shared_ptr<T>, std::shared_ptr<T>> pair, std::pair<std::shared_ptr<T>, std::shared_ptr<T>> otherPair) {
	bool result = pair.first.get() != otherPair.first.get() && pair.second.get() != otherPair.first.get() 
				&& pair.first.get() != otherPair.second.get() && pair.second.get() != otherPair.second.get();
	return result;
}
