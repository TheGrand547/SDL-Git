#include "BigWall.h"

BigWall::BigWall(Rect rect) : rect(rect) {
	this->flags = SOLID | DRAW | BLOCKS_VISIBILTY;
	this->position = rect.getCenter();
}

BigWall::~BigWall() {}

bool BigWall::doesLineCollide(const Line& ray) const {
	return this->rect.doesLineCollide(ray);
}

bool BigWall::overlap(const Rect other) const {
	return this->rect.overlap(other);
}

bool BigWall::overlap(const std::shared_ptr<ThingBase>& other) const {
	return other->overlap(this->rect);
}

float BigWall::originDistance() const {
	return this->rect.getBottomLeft().distanceToPoint(Point(0, 0));
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

void BigWall::addNodes() {
	float horz[] = {-this->rect.getWidth() / 2 - 25, 0, this->rect.getWidth() / 2 + 25};
	float vert[] = {-this->rect.getHeight() / 2 - 25, 0, this->rect.getHeight() / 2 + 25};
	for (float x: horz) {
		for (float y: vert) {
			this->parent->addNode(this->getPosition() + Point(x, y), "CONSTRUCTION");
		}
	}
}

void BigWall::draw(SDL_Renderer* renderer, Point offset) {
	this->rect.draw(renderer, offset);
}

void BigWall::update() {} // This just sits there so why would it need to update anything
