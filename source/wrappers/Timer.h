#pragma once
#include<SDL2/SDL.h>
typedef Uint32 uint32_t;
class Timer {
	private:
		//The clock time when the timer started
		Uint32 mStartTicks;

		//The ticks stored when the timer was paused
		Uint32 mPausedTicks;

		//The timer status
		bool mPaused;
		bool mStarted;
    public:
		//Initializes variables
		Timer() {
			mStartTicks = 0;
			mPausedTicks = 0;
			mPaused = false;
			mStarted = false;
		}

		//The various clock actions
		void start() {
			//Start the timer
			mStarted = true;

			//Unpause the timer
			mPaused = false;

			//Get the current clock time
			mStartTicks = SDL_GetTicks();
			mPausedTicks = 0;
		}
		
		void stop() {
			//Stop the timer
			mStarted = false;

			//Unpause the timer
			mPaused = false;

			//Clear tick variables
			mStartTicks = 0;
			mPausedTicks = 0;
		}
		
		void pause() {
			if(mStarted && !mPaused) {
				//Pause the timer
				mPaused = true;
				//Calculate the paused ticks
				mPausedTicks = SDL_GetTicks() - mStartTicks;
				mStartTicks = 0;
			}
		}
		void unpause() {
			//If the timer is running and paused
			if(mStarted && mPaused){
				//Unpause the timer
				mPaused = false;
				//Reset the starting ticks
				mStartTicks = SDL_GetTicks() - mPausedTicks;
				//Reset the paused ticks
				mPausedTicks = 0;
			}
		}

		//Gets the timer's time
		Uint32 getTicks() {
			Uint32 time = 0;
			//If the timer is running
			if(mStarted){
				//If the timer is paused
				if(mPaused){
					//Return the number of ticks when the timer was paused
					time = mPausedTicks;
				} else {
					//Return the current time minus the start time
					time = SDL_GetTicks() - mStartTicks;
				}
			}
			return time;
		}

		//Checks the status of the timer
		bool isStarted() {
			return mStarted;
		}
		bool isPaused() {
			return mPaused && mStarted;
		}
};
