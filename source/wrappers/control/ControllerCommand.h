#pragma once
#include "CommandBase.h"

template<class T>
class ControllerCommand : public CommandBase {
	private:
		T* target;
		void (*down)(T*);
		void (*up)(T*);
	public:
		ControllerCommand() {
			this->down = [](T*){};
			this->up = [](T*){};
			this->target = NULL;
		}
		
		ControllerCommand(void(*downCommand)(T*), void(*upCommand)(T*), T* target) {
			this->down = downCommand;
			this->up= upCommand;
			this->target = target;
		}
		
		~ControllerCommand() {}
		
		ControllerCommand& operator=(const ControllerCommand& that) {
			this->target = that.target;
			this->down = that.down;;
			this->up = that.up;
			return *this;
		}
		
		void keyDownCommand() {
			this->down(this->target);
		}
		
		void keyUpCommand() {
			this->up(this->target);
		}
};
