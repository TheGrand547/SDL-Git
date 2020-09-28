#pragma once
#ifndef PATH_H
#define PATH_H
#include "../base/EnemyBase.h"
#include "../../wrappers/Timer.h"

class Path {
	protected:
		bool started;
		double ticksDone;
		EnemyBase* target;
		Timer timer;
	public:
		static const int REPEAT;
		static const int SINGLE_LOOP;

		Path(EnemyBase* target = NULL);
		virtual ~Path();
		virtual void stop() = 0;
		virtual void start() = 0;
		virtual bool isFinished() const = 0;
		virtual void modify(double time) = 0;
		bool isPaused() const;
		bool isStarted() const;
		void setTarget(EnemyBase* target);
		void update();
		void pause();
		void unpause();
};
#endif
