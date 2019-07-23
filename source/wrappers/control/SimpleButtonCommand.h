#pragma once
#ifndef SIMPLE_BUTTON_COMMAND_H
#define SIMPLE_BUTTON_COMMAND_H
#include "ButtonCommand.h"
class SimpleButtonCommand : public ButtonCommand {
	private:
		void (*command)();
	public:
		SimpleButtonCommand(void(*command)());
		~SimpleButtonCommand();
		SimpleButtonCommand& operator=(const SimpleButtonCommand& other);
		void execute();
		int DEFAULT();
};
#endif
