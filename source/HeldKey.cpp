#include "HeldKey.h"
#include<iostream>

HeldKey::HeldKey() {
	this->down = false;
	this->toggle = false;
	this->maxHeld = 1;
}

HeldKey::HeldKey(int maxHeld) {
	this->down = false;
	this->toggle = false;
	this->maxHeld = maxHeld;
}

void HeldKey::reset() {
	this->toggle = false;
	this->timer.stop();
}

void HeldKey::set(bool to) {
	this->down = to;
	if (to) {
		if (this->timer.getTicks() == 0) {
			this->timer.start();
		}
		tick();
	} else {
		reset();
	}
}

bool HeldKey::tick() {
	if (this->down) {
		if (this->timer.getTicks() >= this->maxHeld) {
			this->toggle = true;
		} 
	}
	return this->toggle;
}

bool HeldKey::getHeld() {
	return this->toggle;
}
