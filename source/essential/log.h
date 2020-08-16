#pragma once
#include<iostream>
#include<ctime>
#include<chrono>

// Debug, 0 = off, not 0 = on
#define TRACE_MODE 0

void logFormat(const char* file, const char* function, int line);

// Used like printf(...);
#define LOG(...) {logFormat(__FILE__, __PRETTY_FUNCTION__, __LINE__); printf(__VA_ARGS__); printf("\n"); fflush(stdout);}

// Log but only for tracing
#define TRACE(...) if (TRACE_MODE) LOG(__VA_ARGS__);

