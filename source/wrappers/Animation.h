#pragma once
#ifndef ANIMATION_H
#define ANIMATION_H
#include "SpriteSheet.h"
#include "Timer.h"

typedef uint Uint;

class Animation {
	friend class SpriteSheet;
	private:
		SpriteSheet& parent;
		Timer timer;
		Uint currentIndex, duration, endingIndex, interval, startingIndex;
	public:
		Animation(SpriteSheet& parent, Uint startingIndex, Uint endingIndex, Uint duration, Uint interval);
		~Animation();
		void foo();
};
#endif
