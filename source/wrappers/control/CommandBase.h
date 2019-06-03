#pragma once
#ifndef COMMAND_BASE_H
#define COMMAND_BASE_H
class CommandBase {
	public:
		CommandBase();
		virtual ~CommandBase();
		virtual CommandBase& operator=(const CommandBase &other) {
			return *this;
		}
		virtual void keyDownCommand() {} 
		virtual void keyUpCommand() {}
		virtual int DEFAULT();
};
#endif
