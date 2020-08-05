#include "Timer.h"

Timer::Timer() : paused(false), started(false), countedTicks(0), pausedTicks(0), startTicks(0) {}

Timer::~Timer() {}

void Timer::start() {
	this->started = true;
	this->paused = false;
	this->startTicks = SDL_GetTicks();
	this->pausedTicks = 0;
	this->countedTicks = 0;
}

void Timer::stop() {
	this->started = false;
	this->paused = false;
	this->startTicks = 0;
	this->pausedTicks = 0;
	this->countedTicks = 0;
}

bool Timer::isPaused() const {
	return this->paused && this->started;
}

bool Timer::isStarted() const {
	return this->started;
}

double Timer::getFps() const {
	return (double) (this->countedTicks + 1) / ((double) (this->getTicks() + 1) / 1000.f);
}

void Timer::pause() {
	if (this->started && !this->paused) {
		// Pause the timer
		this->paused = true;
		// Calculate the paused ticks
		this->pausedTicks = SDL_GetTicks() - this->startTicks;
		this->startTicks = 0;
	} else this->unpause();
}

void Timer::tick() {
	if (this->countedTicks > 250 || this->countedTicks == 0) {
		this->countedTicks = 0;
		this->start();
	}
	this->countedTicks++;
}

void Timer::unpause() {
	// If the timer is running and paused
	if (this->started && this->paused){
		this->paused = false;
		// Reset the starting ticks
		this->startTicks = SDL_GetTicks() - this->pausedTicks;
		// Reset the paused ticks
		this->pausedTicks = 0;
		this->countedTicks = 0;
	}
}

Uint32 Timer::getTicks() const {
	Uint32 time = 0;
	// If the timer is running
	if (this->started){
		if (this->paused){
			// Return the number of ticks when the timer was paused
			time = this->pausedTicks;
		} else {
			// Return the current time minus the start time
			time = SDL_GetTicks() - this->startTicks;
		}
	}
	return time;
}
