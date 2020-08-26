#pragma once
#include<algorithm>
#include<cmath>
#include<math.h>
#include<set>
#include<stdlib.h>
#include<memory>
#include<utility>
#include<vector>
/* Misc functions with no dependencies */

#define ROUNDING 0.000001

template<typename T>
double radians(T degrees) {
	return degrees * (M_PI / 180.0);
}

template<typename T>
void mMax(T numA, T numB, T& iMin, T& iMax) {
	iMin = (numA > numB) ? numB : numA;
	iMax = (numA > numB) ? numA : numB;
}

bool valueInRange(double value, double min, double max);

template<typename T>
T toTicks(T seconds) {
	return seconds * 1000.f;
}

template<typename T>
T& choice(const std::vector<T>& vector) {
	return vector[rand() % vector.size()];
}

template<typename T>
bool valueInVector(const std::vector<T>& vector, const T& element) {
	return std::find(vector.begin(), vector.end(), element) != vector.end();
}

template<typename T>
bool valueNotInVector(const std::vector<T>& vector, const T& element) {
	return std::find(vector.begin(), vector.end(), element) == vector.end();
}

// TODO: Make this templated for ALL possible containers with T.end() and t.begin()
template<typename T>
bool removeValue(std::vector<T>& type, const T& element) {
	// True: Value removed
	// False: Value not removed
	typename std::vector<T>::iterator iterator = std::find(type.begin(), type.end(), element);
	if (iterator != type.end()) type.erase(iterator);
	return iterator != type.end();
}

template<typename T, typename U>
bool removeValue(std::set<T, U>& type, const T& element) {
	// True: Value removed
	// False: Value not removed
	typename std::set<T, U>::iterator iterator = std::find(type.begin(), type.end(), element);
	if (iterator != type.end()) type.erase(iterator);
	return iterator != type.end();
}
	

double gaussian(double x, double sigma);

template<typename T>
bool shareNoElements(std::pair<std::shared_ptr<T>, std::shared_ptr<T>> pair, std::pair<std::shared_ptr<T>, std::shared_ptr<T>> otherPair) {
	bool result = pair.first.get() != otherPair.first.get() && pair.second.get() != otherPair.first.get() 
				&& pair.first.get() != otherPair.second.get() && pair.second.get() != otherPair.second.get();
	return result;
}
