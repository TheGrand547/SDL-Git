#include "SectorPathFollower.h"

SectorPathFollower::SectorPathFollower(Rect rect) : ThingBase(DRAW | MOVEABLE), box(rect) {}

SectorPathFollower::~SectorPathFollower() {}

bool SectorPathFollower::doesLineCollide(const Line& ray) const {
	return this->box.doesLineCollide(ray);
}

bool SectorPathFollower::overlap(const Rect& other) const {
	return this->box.overlap(other);
}

bool SectorPathFollower::overlap(const std::shared_ptr<ThingBase>& other) const {
	return other->overlap(this->box);
}

double SectorPathFollower::originDistance() const {
	return this->box.getCenter().distanceToPoint();
}

Point SectorPathFollower::collideLine(const Line& ray) const {
	return this->box.collideLine(ray);
}

Point SectorPathFollower::getPosition() const {
	return this->box.getCenter();
}


Rect SectorPathFollower::getRect() const {
	return this->box;
}

void SectorPathFollower::draw(SDL_Renderer* renderer, Point offset) {
	if (!this->texture.isLoaded()) this->texture.loadFromFile(renderer, "resources/temp.png", 10, 10);
	this->texture.draw(renderer, this->box.getCenter() - offset);
}

void SectorPathFollower::update() {
	Point p = this->mine.currentTarget(this->box.getCenter());
	if (p.isNull()) return;
	this->box += p;
}
