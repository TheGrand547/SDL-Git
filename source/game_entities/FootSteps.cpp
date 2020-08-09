#include "FootSteps.h"
#include "../GameInstance.h"

FootSteps::FootSteps() : ThingBase(DRAW) {}

FootSteps::~FootSteps() {}

bool FootSteps::doesLineCollide(const Line& ray) const {
	if (ray.getUnitVector().getFastMagnitude() != 1) LOG("How?");
	return false;
}

bool FootSteps::overlap(const Polygon& other) const {
	// Can only collide with vision lines
	if (other.getArea() == -1) LOG("What the flying fuck did you do");
	return false;
}

bool FootSteps::overlap(const std::shared_ptr<ThingBase>& other) const {
	// Can only collide with vision lines
	if (other->getBoundingRect().getArea() == -1) LOG("What the flying fuck did you do");
	return false;
}

double FootSteps::originDistance() const {
	return 50.52;	
}

Point FootSteps::collideLine(const Line& ray) const {
	if (ray.getUnitVector().getFastMagnitude() != 1) LOG("How?");
	return Point();	
}

Point FootSteps::getPosition() const {
	// This doesn't really *have* a position
	return Point();
}

Rect FootSteps::getBoundingRect() const {
	return Rect();
}

void FootSteps::draw(SDL_Renderer* renderer, Point offset) {
	Rect drawin(0, 0, 10, 10);
	drawin.setColorChannels(0x00, 0x00, 0xF0, 0x80);
	for (Point point: this->storage) {
		drawin.setCenter(point);
		drawin.draw(renderer, offset);
	}
}

void FootSteps::update() {
	if (!this->interval.isStarted()) this->interval.start();
	if (this->interval.getTicks() > 500) {
		// TODO: Add distance check thingy
		this->interval.start();
		this->storage.push_back(this->parent->getPlayer()->getBoundingRect().getCenter());
		if (this->storage.size() > 10) this->storage.pop_front();
	}
} 
