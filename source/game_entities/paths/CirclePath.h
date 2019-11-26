#pragma once
#include<math.h>
#include "../../wrappers/Timer.h"
#include "Path.h"

class CirclePath : public Path {
	protected:
		/* Standard Parametric Equation for a Cirle
		 * x = r * cos(t / a)
		 * y = r * sin(t / a)
		 * When CirclePath is created by a PathManager, its stored somewhere not doing anything
		 * When PathManager calls a Path it is then updated every frame until isFinished() returns false
		 * When called it checks how many milliseconds it has been since it was called, and if that number is 
		 * greater than 10ms it runs an update. Updates are defined as such
		 * dx = r / a * -sin(t / a)
		 * dy = r / a * cos(t / a)
		 * Where r is the intended radius and 2pi * a is the period in seconds */
		float outsideMult, periodModify;
		int maxTicks, plot;
		int startingTicks = 0;
		int startingMaxTicks = 0;
	public:
		CirclePath();
		CirclePath(int radius = 10, float periodModify = .5, int maxTicks = Path::SINGLE_LOOP, bool clockwise = true, int startingTicks = 0);
		~CirclePath();
		void stop();
		void start();
		bool isFinished() const;
		void modify(float time);
};
