#include "BigWall.h"
#include "../GameInstance.h"

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

bool BigWall::overlap(const Polygon& other, [[maybe_unused]] const int& flags) const {
	return this->rect.overlap(other);
}

bool BigWall::overlap(const std::shared_ptr<ThingBase>& other) const {
	return other->overlap(this->rect);
}

bool BigWall::overlap(const std::shared_ptr<ThingBase>& other, const int& flags) const {
	if (flags & SUPER_MOVEMENT) {
		// Reduce to diagonal rectangle to determine priority movement
		std::vector<Point> pts;
		for (Line line: this->rect.getLines()) {
			pts.push_back(line.midPoint());
		}
		return other->overlap(Rect(pts[0], pts[1], pts[2], pts[3]));
	} else {
		return other->overlap(this->rect);
	}
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

Rect BigWall::getBoundingRect() const {
	return this->rect.getBoundingRect();
}

void BigWall::draw() {
	this->rect.setColorChannels(0x00, 0x00, 0xFF, 0xFF);
	this->rect.drawFilled(this->parent->getRenderer());
}
