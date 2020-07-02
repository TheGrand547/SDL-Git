#pragma once
#ifndef FILE_STUCTURE_ANALYZER_H
#define FILE_STRUTURE_ANALYZER_H
#include "../GameInstance.h"
#include<string>

// Takes a file input and creates all the things in the level from it
void analyzeFile(const std::string& source, GameInstance& instance);

#endif
