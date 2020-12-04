#pragma once
#ifndef TIMER_H
#define TIMER_H
#include "../essential/constants.h"
#include <SDL2/SDL.h>

typedef uint32_t Uint32;

// Lightly modified from the timer on lazyfoo.net
class Timer {
	protected:
		bool paused, started;
		int countedTicks;
		Uint32 pausedTicks, startTicks;
    public:
		Timer();
		~Timer();
		bool isStarted() const;
		bool isPaused() const;
		double getFps() const;
		Uint32 getTicks() const;
		void start();
		void stop();
		void pause();
		void unpause();
		void tick();
};
#endif
