#pragma once
#ifndef COMMAND_BASE_H
#define COMMAND_BASE_H
class CommandBase {
	public:
		CommandBase();
		virtual ~CommandBase() = 0;
		virtual void execute() = 0;
};
#endif
