#pragma once
#include<iostream>
#include<ctime>
#include<chrono>

void logFormat(const char* file, const char* function, int line);

// Used like printf(...);
#define LOG(...) {logFormat(__FILE__, __PRETTY_FUNCTION__, __LINE__); printf(__VA_ARGS__); printf("\n"); fflush(stdout);}
