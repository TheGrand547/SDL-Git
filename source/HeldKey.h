#ifndef HELD_KEY_H
#define HELD_KEY_H
/* TODO: Rewrite class based on SDL_GetTicks so its not framerate dependent */

class HeldKey {
	private:
		bool down, toggle;
		int framesHeld, keySignature, maxHeld;
	public:
		HeldKey();
		HeldKey(int keySignature, int maxHeld);
		~HeldKey() {}
		void reset();
		void set(bool to);
		bool tick();
		int getFrames(); /* Returns number of frames it has been held down */
		bool getHeld(); /* Returns true if the key has been held down past its threshold */
};
#endif
