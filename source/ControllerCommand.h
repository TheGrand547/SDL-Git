#pragma once

/** Who doesn't love long class names :D **/
template<class T, class U> // SLOPPY, YOU SHOULD BE SAD
class ControllerCommand {
	private:
		T* target;
		// TODO: Write the 'method' class, or just use lambdas
		void (*function)(T*, U);
	public:
		ControllerCommand(void(*function)(T*, U), T* target) {
			this->function = function;
			this->target = target;
		}
		
		~ControllerCommand() {
			delete this->function;
		}
		
		void execute(U x) {
			this->function(this->target, x);
		}
};
