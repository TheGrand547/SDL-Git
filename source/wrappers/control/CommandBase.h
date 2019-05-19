#pragma once
#ifndef COMMAND_BASE_H
#define COMMAND_BASE_H
class CommandBase {
	public:
		CommandBase();
		virtual ~CommandBase();
		virtual CommandBase& operator=(const CommandBase &other) {
			std::cout << "dammit";
			return *this;
		}
		virtual void keyDownCommand() {std::cout << "f";} 
		virtual void keyUpCommand() {std::cout << "fe";}
};
#endif
