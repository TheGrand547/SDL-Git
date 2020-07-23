#pragma once
#ifndef FILE_STUCTURE_ANALYZER_H
#define FILE_STRUTURE_ANALYZER_H
#include "../GameInstance.h"
#include<iostream>
#include<fstream>
#include<string>

typedef std::map<std::string, std::string> StringMap;

Rect rectFromString(const std::string& string);

// Takes a file input and creates all the things in the level from it
void analyzeFile(const std::string& source, GameInstance& instance);
void analyzeStructure(const std::string& source, GameInstance& instance, StringMap& map);

#endif
