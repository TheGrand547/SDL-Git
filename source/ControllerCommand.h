#pragma once

/** Who doesn't love long class names :D **/
template<class T, class U> // SLOPPY, YOU SHOULD BE SAD
class ControllerCommand {
	private:
		T* target;
		void (*function)(T*, U);
		U param;
	public:
		ControllerCommand(void(*function)(T*, U), T* target, U param) {
			this->function = function;
			this->target = target;
			this->param = param;
		}
		
		~ControllerCommand() {}
		
		ControllerCommand& operator=(const ControllerCommand& that) {
			this->target = that.target;
			this->function = that.function;
			this->param = that.param;
			return *this;
		}
		
		void execute() {
			this->function(this->target, this->param);
		}
};
