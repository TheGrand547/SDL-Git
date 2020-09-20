#include "SectorPathFollower.h"

SectorPathFollower::SectorPathFollower(Rect rect) : ThingBase(DRAW | MOVEABLE), box(rect), mine(this) {}

SectorPathFollower::~SectorPathFollower() {}

bool SectorPathFollower::doesLineCollide(const Line& ray) const {
	return this->box.doesLineCollide(ray);
}

bool SectorPathFollower::isAlive() const {
	return !this->parent->getPlayer()->overlap(this->box);
}

bool SectorPathFollower::overlap(const Polygon& other) const {
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
	return this->box.getTopLeft();
}


Rect SectorPathFollower::getBoundingRect() const {
	return this->box;
}

void SectorPathFollower::draw() {
	if (!this->texture.isLoaded()) {
		this->texture.load("resources/temp.png");
		this->texture.scale(10, 10);
	}
	this->mine.draw();
	this->texture.draw(this->getPosition() - this->parent->getRenderer());
}

void SectorPathFollower::update() {
	if (this->parent->getPlayer()->overlap(this->box)) this->parent->queueRemoval(this->shared_from_this());
	Point p = this->mine.currentTarget(this->box.getCenter());
	double value = this->movement.getValue();
	if (p.isNull() || !value) return;
	this->box += p * value * 100;
	this->parent->gameState["PathFinished"] = (int) this->mine.isFinished();
}
