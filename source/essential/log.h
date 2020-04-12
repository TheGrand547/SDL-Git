#pragma once
#include<iostream>

#define LOG_FORMAT(file, function, number) printf("[%s][%s] Line %i: ", file, function, number)

// Used like printf(...);
#define LOG(...) LOG_FORMAT(__FILE__, __PRETTY_FUNCTION__, __LINE__); \
				printf(__VA_ARGS__); \
				printf("\n"); \
				fflush(stdout);
