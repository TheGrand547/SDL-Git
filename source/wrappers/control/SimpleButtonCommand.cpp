#include "SimpleButtonCommand.h"

SimpleButtonCommand::SimpleButtonCommand(void(*command)()) {
	this->command = command;
}

SimpleButtonCommand::~SimpleButtonCommand() {}

SimpleButtonCommand& SimpleButtonCommand::operator=(const SimpleButtonCommand& other) {
	this->command = other.command;
	return *this;
}

void SimpleButtonCommand::execute() {
	this->command();
}

int SimpleButtonCommand::DEFAULT() {
	return 0;
}
