#pragma once
#ifndef SIMPLE_BUTTON_COMMAND_H
#define SIMPLE_BUTTON_COMMAND_H
#include "ButtonCommand.h"
template<class T>
class SimpleButtonCommand : public ButtonCommand {
	private:
		T* arg;
		void (*command)(T*);
	public:
		SimpleButtonCommand(void(*command)(T*), T* arg) {
			this->arg = arg;
			this->command = command;
		}
		
		~SimpleButtonCommand() {}
		
		SimpleButtonCommand& operator=(const SimpleButtonCommand& other) {
			this->arg = other.arg;
			this->command = other.arg;
			return *this;
		}
		
		void execute() {
			this->command(arg);
		}
		
		int DEFAULT() {
			return 0;
		}
};
#endif
