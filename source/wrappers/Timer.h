#pragma once
#include "../essential/constants.h"
#include<SDL2/SDL.h>
typedef Uint32 uint32_t;

/** Lightly modified from the timer on lazyfoo.net **/
class Timer {
	private:
		Uint32 mStartTicks, mPausedTicks;
		bool mPaused, mStarted;
		int countedTicks;
    public:
		Timer();
		~Timer();
		void start();
		void stop();
		void pause();
		void unpause();
		void tick();
		float getFps();
		float getRatio();
		Uint32 getTicks();
		bool isStarted();
		bool isPaused();
};
