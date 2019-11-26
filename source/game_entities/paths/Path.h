#pragma once
#include "../base/EnemyBase.h"
#include "../../wrappers/Timer.h"

class Path {
	protected:
		Timer timer;
		float ticksDone;
		EnemyBase* target;
		bool started = false;
	public:
		static const int REPEAT = 0;
		static const int SINGLE_LOOP = -2;
		
		Path(EnemyBase* target = NULL);
		bool isStarted() const;
		virtual ~Path();
		virtual void stop() = 0;
		virtual void start() = 0;
		virtual bool isFinished() const = 0;
		virtual void modify(float time) = 0;
		void setTarget(EnemyBase* target);
		void update();
		void pause();
		void unpause();
		bool isPaused();
};
