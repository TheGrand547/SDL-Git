#pragma once

/* TODO: Rewrite class based on SDL_GetTicks so its not framerate dependent */

class HeldKey {
	private:
		bool down, toggle;
		int framesHeld, keySignature, maxHeld;
	public:
		HeldKey() {
			this->down = false;
			this->toggle = false;
			this->keySignature = 0;
			this->framesHeld = 0;
			this->maxHeld = 0;
		}
		
		HeldKey(int keySignature, int maxHeld) {
			this->down = false;
			this->toggle = false;
			this->keySignature = keySignature;
			this->framesHeld = 0;
			this->maxHeld = maxHeld;
		}
		
		~HeldKey() {}
		
		void reset() {
			this->toggle = false;
			this->framesHeld = 0;
		}
		
		void set(bool to) {
			if (this->down) {
				tick();
			} else {
				reset();
			}
		}
		
		bool tick() {
			if (this->down) {
				/* If '+=' is replaced with ++ it gives segmentation fault, odd */
				this->framesHeld++;
				if (this->framesHeld >= this->maxHeld) {
					this->toggle = true;
				} 
			}
			return this->toggle;
		}
		
		/* Returns number of frames it has been held down */
		int getFrames() {
			return this->framesHeld;
		}
		
		/* Returns true if the key has been held down past its threshold */
		bool getHeld() {
			return this->toggle;
		}
};
