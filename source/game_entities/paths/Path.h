#pragma once
#include "../../wrappers/Timer.h"

template<class T>
class Path {
	protected:
		Timer* timer;
		float ticksDone, ticksOver;
		T* target;
	public:
		static const int REPEAT = 0;
		static const int SINGLE_LOOP = -2;
		
		Path(T* target) {
			this->timer = new Timer();
			this->ticksDone = 0;
			this->ticksOver = 0;
			this->target = target;
		}
		
		~Path() {
			delete this->timer;
		}
		
		void start() {
			this->timer->start();
		}
		
		virtual bool isFinished() = 0;
		
		virtual void modify(float delta = 0) = 0;
		
		void update() {
			this->ticksOver = this->timer->getTicks();
			this->timer->start();
			this->modify(this->ticksOver);
			this->ticksDone += this->ticksOver / 10;
		}
};
