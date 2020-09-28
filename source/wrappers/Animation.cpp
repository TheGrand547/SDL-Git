#include "Animation.h"

Animation::Animation(Uint startingIndex, Uint endingIndex, Uint interval) : started(false), endingIndex(endingIndex), 
					interval(interval), startingIndex(startingIndex), currentIndex(0) {}

Animation::Animation(const Animation& other) : started(other.started), endingIndex(other.endingIndex), 
					interval(other.interval), startingIndex(other.startingIndex), currentIndex(other.currentIndex) {}

Animation::~Animation() {}

Animation& Animation::operator=(const Animation& other) {
	if (this != &other) {
		this->started = other.started;
		this->currentIndex = other.currentIndex;
		this->endingIndex = other.endingIndex;
		this->interval = other.interval;
		this->startingIndex = other.startingIndex;
	}
	return *this;
}

bool Animation::isReal() const {
	return this->interval;
}

bool Animation::isStarted() const {
	return this->started;
}

bool Animation::update() {
	if (this->started && this->timer.getTicks() >= this->interval) {
		this->currentIndex++;
		this->started = this->currentIndex <= this->endingIndex;
		this->timer.start();
	}
	return this->started;
}

void Animation::exit() {
	this->currentIndex = this->startingIndex;
	this->started = false;
	this->timer.stop();
}

void Animation::pause() {
	this->timer.pause();
}

void Animation::start() {
	this->started = true;
	this->timer.start();
	this->currentIndex = this->startingIndex;
}

void Animation::reset() {
	this->start();
}
