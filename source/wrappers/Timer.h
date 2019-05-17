#pragma once
#include<SDL2/SDL.h>
typedef Uint32 uint32_t;

/** Lightly modified from the timer on lazyfoo.net **/
class Timer {
	private:
		Uint32 mStartTicks;
		Uint32 mPausedTicks;
		bool mPaused;
		bool mStarted;
    public:
		Timer();
		~Timer();
		void start();
		void stop();
		void pause();
		void unpause();
		Uint32 getTicks();
		bool isStarted();
		bool isPaused();
};
