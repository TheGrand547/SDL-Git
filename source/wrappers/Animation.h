#pragma once
#ifndef ANIMATION_H
#define ANIMATION_H

class Animation;

#include "SpriteSheet.h"
#include "Timer.h"

typedef uint Uint;

class Animation {
	private:
		bool started;
		Timer timer;
		Uint endingIndex, interval, startingIndex;
	public:
		Uint currentIndex;
		
		Animation(Uint startingIndex = 0, Uint endingIndex = 0, Uint interval = 0);
		Animation(const Animation& other);
		~Animation();
		Animation& operator=(const Animation& other);
		bool isReal() const;
		bool update();
		void exit();
		void pause();
		void start();
		void reset(); // Alias of start to be more specific
};
#endif
