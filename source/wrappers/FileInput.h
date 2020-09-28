#pragma once
#ifndef FILE_INPUT_H
#define FILE_INPUT_H
#include <iostream>
#include <fstream>
#include <string>

class FileInput {
	protected:
		bool open;
		std::ifstream file;
		std::string currentLine;
	public:
		FileInput();
		FileInput(const std::string& filename);
		~FileInput();
		bool atEOS() const;
		bool isOpen() const;
		std::string nextChar();
		std::string nextLine();
		std::string nextWord();
		void close();
		void open(const std::string& filename);
};
#endif
