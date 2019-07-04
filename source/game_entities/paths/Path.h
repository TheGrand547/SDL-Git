#pragma once
#include "../../wrappers/Timer.h"

template<class T>
class Path {
	protected:
		Timer timer;
		float ticksDone;
		T* target;
	public:
		static const int REPEAT = 0;
		static const int SINGLE_LOOP = -2;
		
		Path() {
			this->ticksDone = 0;
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
			float tmp = this->timer.getTicks();
			this->modify(tmp / 10);
			this->timer.start();
		}
		
		void pause() {
			this->timer.pause();
		}
		
		void unpause() {
			this->timer.unpause();
		}
};
