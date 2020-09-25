#pragma once
#include<iostream>
#include<ctime>
#include<chrono>

void logTimeNow();
void logFormat(const char* file, const char* function, int line);

// Used like printf(...);
#define LOG(...) {logFormat(__FILE__, __PRETTY_FUNCTION__, __LINE__); printf(__VA_ARGS__); printf("\n"); fflush(stdout);}

// Log but only for tracing


// TODO: figure out how to do this across all compile zones or whatever idk
#ifdef TRACE_MODE
#define TRACE(...) {logFormat(__FILE__, __PRETTY_FUNCTION__, __LINE__); printf("[TRACE] "); printf(__VA_ARGS__); printf("\n"); fflush(stdout);};
#else
#define TRACE(...)
#endif
