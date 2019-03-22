#pragma once
class HeldKey {
	private:
		bool *down, *toggle;
		int *framesHeld, *keySignature, *maxHeld;
	public:
		HeldKey(int keySignature, int maxHeld) {
			this->down = new bool(false);
			this->toggle = new bool(false);
			this->keySignature = new int(keySignature);
			this->framesHeld = new int(0);
			this->maxHeld = new int(maxHeld);
		}
		
		~HeldKey() {
			delete this->down;
			delete this->framesHeld;
			delete this->keySignature;
			delete this->maxHeld;
			delete this->toggle;
		}
		
		void reset() {
			*(this->toggle) = false;
			*(this->framesHeld) = 0;
		}
		
		void set(bool to) {
			*(this->down) = to;
			if (to == true) {
				tick();
			} else {
				reset();
			}
		}
		
		bool tick() {
			if (*(this->down)) {
				*(this->framesHeld) += 1;
				if (*(this->framesHeld) >= *(this->maxHeld)) {
					*(this->toggle) = true;
				} 
			}
			return *(this->toggle);
		}
		
		int get() {
			return *(this->framesHeld);
		}
};
