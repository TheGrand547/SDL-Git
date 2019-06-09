#pragma once
#include "../../wrappers/Timer.h"

template<class T>
class Path {
	protected:
		Timer timer;
		float ticksDone, ticksOver;
		T* target;
	public:
		static const int REPEAT = 0;
		static const int SINGLE_LOOP = -2;
		
		Path() {
			this->ticksDone = 0;
			this->ticksOver = 0;
			this->target = NULL;
		}
		
		virtual ~Path() {
			this->target = NULL;
		}
		
		virtual void stop() {
			this->timer.stop();
			this->ticksDone = 0;
		}
		
		void start() {
			this->timer.start();
		}
		
		virtual bool isFinished() = 0;
		
		virtual void modify(float time) = 0;
		
		void setTarget(T* target) {
			this->target = target;
		}
		
		void update() {
			this->ticksOver = this->timer.getTicks();
			this->timer.start();
			this->modify(this->ticksOver / 10);
		}
		
		void pause() {
			this->timer.pause();
		}
		
		void unpause() {
			this->timer.unpause();
		}
};
