#include "Timer.h"

//Initializes variables
Timer::Timer() {
	this->mStartTicks = 0;
	this->mPausedTicks = 0;
	this->mPaused = false;
	this->mStarted = false;
}
Timer::~Timer() {}

void Timer::start() {
	this->mStarted = true;
	this->mPaused = false;
	this->mStartTicks = SDL_GetTicks();
	this->mPausedTicks = 0;
}

void Timer::stop() {
	this->mStarted = false;
	this->mPaused = false;
	this->mStartTicks = 0;
	this->mPausedTicks = 0;
}

void Timer::pause() {
	if(this->mStarted && !this->mPaused) {
		//Pause the timer
		mPaused = true;
		//Calculate the paused ticks
		mPausedTicks = SDL_GetTicks() - mStartTicks;
		mStartTicks = 0;
		return;
	}
	this->unpause();
}
void Timer::unpause() {
	//If the timer is running and paused
	if(mStarted && mPaused){
		mPaused = false;
		//Reset the starting ticks
		mStartTicks = SDL_GetTicks() - mPausedTicks;
		//Reset the paused ticks
		mPausedTicks = 0;
	}
}

Uint32 Timer::getTicks() {
	Uint32 time = 0;
	//If the timer is running
	if(mStarted){
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

bool Timer::isStarted() {
	return mStarted;
}
bool Timer::isPaused() {
	return mPaused && mStarted;
}
