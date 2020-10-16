#pragma once
#include <ctime>
#include <chrono>
#include <iostream>

// Remove for alpha/beta/final releases
//#define NDEBUG

void logTimeNow();
void logFormat(const char* file, const char* function, const char* type, int line);

// Used like printf(...);
#define LOG(...) {logFormat(__FILE__, __PRETTY_FUNCTION__, "Log", __LINE__); printf(__VA_ARGS__); printf("\n"); fflush(stdout);}

// Log but only for tracing
// TODO: figure out how to do this across all compile zones or whatever idk
#ifdef TRACE_MODE
#define TRACE(...) {logFormat(__FILE__, __PRETTY_FUNCTION__, "Trace", __LINE__); printf(__VA_ARGS__); printf("\n"); fflush(stdout);}
#else
#define TRACE(...)
#endif
