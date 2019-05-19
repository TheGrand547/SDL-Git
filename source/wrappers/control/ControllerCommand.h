#pragma once
#include "CommandBase.h"

/** Who doesn't love long class names :D **/
template<class T>
class ControllerCommand : public CommandBase {
	private:
		T* target;
		void (*down)(T*);
		void (*up)(T*);
	public:
		ControllerCommand() {
			this->down = [](T*){std::cout << "shit";};
			this->up = [](T*){std::cout << "goddammit";};
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
			std::cout << "D" << std::endl;
			this->down(this->target);
		}
		
		void keyUpCommand() {
			std::cout << "e" << std::endl;
			this->up(this->target);
		}
};
