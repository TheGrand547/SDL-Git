#include "Animation.h"

Animation::Animation(SpriteSheet& parent, Uint startingIndex, Uint endingIndex, Uint duration, Uint interval) : parent(parent), currentIndex(0),
					duration(duration), endingIndex(endingIndex), interval(interval), startingIndex(startingIndex) {
	this->timer.start();
}

Animation::~Animation() {}

// Temporary function to appease compiler
void Animation::foo() { 
	std::cout << &parent << ", " << currentIndex << std::endl;
	this->startingIndex++;
	this->endingIndex++;
	this->duration++;
	this->interval++;
}
