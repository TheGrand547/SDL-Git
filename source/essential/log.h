#pragma once
#include<iostream>

template<typename T> void opop(std::ostream& ostream, T t) {
	ostream << t;
}

template<typename T, typename... Args> void opop(std::ostream& ostream, T t, Args... args) {
	ostream << t;
	opop(ostream, args...);
}

template<typename T> void makeLogs(const char* file, const char* function, const int lineNumber, T t) {
	std::cout << "[" << file << "][" << function << "] Line " << lineNumber << ": " << t << std::endl;
}

template<typename... Args> void makeLogs(const char* file, const char* function, const int lineNumber, Args... args) {
	std::cout << "[" << file << "][" << function << "] Line " << lineNumber << ": ";
	opop(std::cout, args...);
	std::cout << std::endl;
}

#define LOG_FORMAT(file, function, number) "[" << file << "][" << function << "] Line " << number << ": "
#define LOG(...) makeLogs(__FILE__, __PRETTY_FUNCTION__, __LINE__, __VA_ARGS__)
