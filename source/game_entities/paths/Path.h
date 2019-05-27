#pragma once
#include "../../wrappers/Timer.h"

template<class T>
class Path {
	protected:
		Timer* timer;
		int ticksDone, ticksOver;
		T* target;
	public:
		static const int REPEAT = 0;
		static const int SINGLE_LOOP = -2;
		
		Path() {
			this->timer = new Timer();
			this->ticksDone = 0;
			this->ticksOver = 0;
			this->target = NULL;
		}
		
		virtual ~Path() {
			delete this->timer;
			this->target = NULL;
		}
		
		virtual void stop() {
			this->timer->stop();
			this->ticksDone = 0;
		}
		
		void start() {
			this->timer->start();
		}
		
		virtual bool isFinished() = 0;
		
		virtual void modify() = 0;
		
		void setTarget(T* target) {
			this->target = target;
		}
		
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
