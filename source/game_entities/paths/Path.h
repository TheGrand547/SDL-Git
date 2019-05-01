#pragma once
#include "../../wrappers/Timer.h"

template<class T>
class Path {
	protected:
		Timer* timer;
		int ticksDone, ticksOver;
		T* target;
	public:
		Path(T* target) {
			this->timer = new Timer();
			this->ticksDone = 0;
			this->ticksOver = 0;
			this->target = target;
		}
		
		~Path(){
			delete this->timer;
		}
		
		void start() {
			this->timer->start();
		}
		
		virtual void modify() = 0;
		
		void update() {
			this->ticksOver += this->timer->getTicks();
			this->timer->start();
			for (int i = 10; i <= this->ticksOver; i += 10) {
				this->modify();
				this->ticksDone++;
			}
			this->ticksOver %= 10;
		}
};
