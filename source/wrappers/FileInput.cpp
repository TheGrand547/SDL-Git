#include "FileInput.h"

// TODO: test and stuff
FileInput::FileInput() : open(false), currentLine("") {}

FileInput::FileInput(const std::string& filename) {
	this->open(filename);
}

FileInput::~FileInput() {
	this->close();
}

bool FileInput::atEos() const {
	return !this->open || this->file.eof();
}

bool FileInput::isOpen() const {
	return this->open;
}

std::string FileInput::nextChar() {
	std::string character = "";
	if (this->isOpen()) {
		// I swear this isn't sloppy
		// ok it is sloppy but i gotta say it isn't
		if (!this->currentLine.compare("")) {
			this->currentLine = this->nextLine();
		}
		if (!this->currentLine.compare("")) {
			character = this->currentLine[0];
			if (this->currentLine.length() > 1) this->currentLine = this->currentLine.substr(1);
			else this->currentLine = "";
		}
	}
	return character;
}

std::string FileInput::nextLine() {
	std::string value = "";
	if (!this->currentLine.compare("")) {
		if (!this->atEos()) {
			getline(this->file, value);
		}
	} else {
		value = this->currentLine;
		this->currentLine = "";
	}
	return value;
}

std::string FileInput::nextWord() {
	// TODO: Fill in, low priority
	return this->nextChar();
}

void FileInput::close() {
	if (this->isOpen()) {
		this->open = false;
		this->file.close();
	}
}

void FileInput::open(const std::string& filename) {
	this->file.open(filename);
	this->open = this->file.is_open();
}
