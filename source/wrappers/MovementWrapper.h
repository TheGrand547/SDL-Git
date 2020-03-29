#pragma once
#idndef MOVEMENT_WRAPPER_H
#define MOVEMENT_WRAPPER_H
#include "Timer.h"

class MovementWrapper {
	private:
		Timer timer;
	public:
		MovementWrapper();
		~MovementWrapper();
		double getValue();
};
#endif

