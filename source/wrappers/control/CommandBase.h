#pragma once
#ifndef COMMAND_BASE_H
#define COMMAND_BASE_H
class CommandBase {
	public:
		CommandBase();
		virtual ~CommandBase();
		virtual void keyDownCommand();
		virtual void keyUpCommand();
		virtual int DEFAULT();
};
#endif
