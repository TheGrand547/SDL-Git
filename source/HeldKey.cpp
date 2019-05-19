#include "HeldKey.h"
#include<iostream>

HeldKey::HeldKey() {
	this->down = false;
	this->toggle = false;
	this->framesHeld = 0;
	this->maxHeld = 0;
}

HeldKey::HeldKey(int maxHeld) {
	this->down = false;
	this->toggle = false;
	this->framesHeld = 0;
	this->maxHeld = maxHeld;
}

void HeldKey::reset() {
	this->toggle = false;
	this->framesHeld = 0;
}

void HeldKey::set(bool to) {
	this->down = to;
	if (to) {
		tick();
	} else {
		reset();
	}
}

bool HeldKey::tick() {
	if (this->down) {
		this->framesHeld++;
		if (this->framesHeld >= this->maxHeld) {
			this->toggle = true;
		} 
	}
	return this->toggle;
}


int HeldKey::getFrames() {
	return this->framesHeld;
}

bool HeldKey::getHeld() {
	return this->toggle;
}
