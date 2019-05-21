#ifndef HELD_KEY_H
#define HELD_KEY_H
#include "wrappers/Timer.h"
/* TODO: Rewrite class based on SDL_GetTicks so its not framerate dependent */

class HeldKey {
	private:
		bool down, toggle;
		Timer timer;
	public:
		int maxHeld;
		HeldKey();
		HeldKey(int maxHeld);
		~HeldKey();
		void reset();
		void set(bool to);
		bool tick();
		bool getHeld(); /* Returns true if the key has been held down past its threshold */
};
#endif
