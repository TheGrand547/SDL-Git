#pragma once
#ifndef MISC_H
#define MISC_H
#include <algorithm>
#include <cmath>
#include <memory>
#include <set>
#include <stdlib.h>
#include <utility>
#include <vector>
// Misc functions with no dependencies

#define ROUNDING 0.000001

inline bool isZero(const double& num);

inline double toTicks(const double& num);

bool valueInRange(const double& value, const double& min, const double& max);

template<typename T> void minMax(T a, T b, T& min, T& max) {
	min = (a > b) ? b : a;
	max = (a > b) ? a : b;
}

template<typename T> T& choice(const std::vector<T>& vector) {
	return vector[rand() % vector.size()];
}

template<typename T> bool valueInVector(const std::vector<T>& vector, const T& element) {
	return std::find(vector.begin(), vector.end(), element) != vector.end();
}

template<typename T> bool valueNotInVector(const std::vector<T>& vector, const T& element) {
	return std::find(vector.begin(), vector.end(), element) == vector.end();
}

template<typename T, typename U> bool removeValue(T& type, const U& element) {
	// True: Value removed
	// False: Value not removed
	typename T::iterator iterator = std::find(std::begin(type), std::end(type), element);
	if (iterator != std::end(type)) type.erase(iterator);
	return iterator != std::end(type);
}

template<typename T> bool shareNoElements(std::pair<std::shared_ptr<T>, std::shared_ptr<T>> pair, std::pair<std::shared_ptr<T>, std::shared_ptr<T>> otherPair) {
	bool result = pair.first.get() != otherPair.first.get() && pair.second.get() != otherPair.first.get() 
				&& pair.first.get() != otherPair.second.get() && pair.second.get() != otherPair.second.get();
	return result;
}


// ----Inline Definitions----
inline bool isZero(const double& num) {
	return std::abs(num) < ROUNDING;
}

inline double toTicks(const double& num) {
	return num * 1000.f;
}
#endif
