#pragma once
#ifndef FILE_INPUT_H
#define FILE_INPUT_H
#include<iostream>
#include<fstream>
#include<string>

class FileInput {
	protected:
		bool open;
		std::ifstream file;
	public:
		FileInput();
		~FileInput();
		bool isOpen() const;
		bool atEOS() const;
		std::string nextChar();
		std::string nextLine();
		std::string nextWord();
		void open(const std::string& file);
		void close();
		
};
#endif
