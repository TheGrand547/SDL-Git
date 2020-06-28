#include "BigWall.h"

BigWall::BigWall(Rect rect) : ThingBase(SOLID | DRAW | BLOCKS_VISIBILTY), rect(rect) {
	this->position = rect.getCenter();
}

BigWall::~BigWall() {}

bool BigWall::doesLineCollide(const Line& ray) const {
	return this->rect.doesLineCollide(ray);
}

bool BigWall::overlap(const Polygon& other) const {
	return this->rect.overlap(other);
}

bool BigWall::overlap(const std::shared_ptr<ThingBase>& other) const {
	return other->overlap(this->rect);
}

double BigWall::originDistance() const {
	return this->rect.getBottomRight().distanceToPoint(Point(0, 0));
}

Point BigWall::collideLine(const Line& ray) const {
	return this->rect.collideLine(ray);
}

Point BigWall::getPosition() const {
	return this->rect.getCenter();
}

Rect BigWall::getRect() const {
	return this->rect;
}

void BigWall::draw(SDL_Renderer* renderer, Point offset) {
	this->rect.draw(renderer, offset);
}
