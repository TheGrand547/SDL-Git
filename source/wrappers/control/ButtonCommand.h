#pragma once
#ifndef BUTTON_COMMAND_H
#define BUTTON_COMMAND_H
class ButtonCommand {
	public:
		ButtonCommand() {}
		virtual ~ButtonCommand() {}
		virtual void execute() = 0;
};
#endif
