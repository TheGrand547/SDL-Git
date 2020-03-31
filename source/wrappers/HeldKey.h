#ifndef HELD_KEY_H
#define HELD_KEY_H
#include "Timer.h"

class HeldKey {
	private:
		bool down, toggle;
		Timer timer;
	public:
		uint maxHeld;
		HeldKey();
		HeldKey(int maxHeld);
		~HeldKey();
		void reset();
		void set(bool to);
		bool getHeld(); /* Returns true if the key has been held down past its threshold */
};
#endif
