#pragma once
#include "../base/EnemyBase.h"
#include "../../wrappers/Timer.h"

class Path {
	protected:
		Timer timer;
		float ticksDone;
		EnemyBase* target;
	public:
		static const int REPEAT = 0;
		static const int SINGLE_LOOP = -2;
		
		Path(EnemyBase* target = NULL);
		virtual ~Path();
		virtual void stop();
		void start();
		virtual bool isFinished() = 0;
		virtual void modify(float time) = 0;
		void setTarget(EnemyBase* target);
		void update();
		void pause();
		void unpause();
};
