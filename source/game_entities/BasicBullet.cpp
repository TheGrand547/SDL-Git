#include "BasicBullet.h"
#include "../GameInstance.h"

BasicBullet::BasicBullet(double angle, double speed) : ThingBase(MOVEABLE | DRAW), angle(angle), delta(Point::vectorFromAngle(angle) * speed) {
	this->setImage();
}

BasicBullet::BasicBullet(Point delta) : ThingBase(MOVEABLE | DRAW), angle(Point::angleFromVector(delta) * -180.0 / M_PI), delta(delta) {
	this->setImage();
	this->position = {50, 50};
}

BasicBullet::~BasicBullet() {}

bool BasicBullet::doesLineCollide(const Line& ray) const {
	return ray.isOrthogonal(Line(Point(), Point()));
}

bool BasicBullet::overlap(const Polygon& other) const {
	return other.isAxisAligned();
}

bool BasicBullet::overlap(const ThingPtr& other) const {
	return other->getBoundingRect().isAxisAligned();
}

double BasicBullet::originDistance() const {
	return this->position.distanceToPoint();
}
Point BasicBullet::getPosition() const {
	return this->position;
}

Point BasicBullet::collideLine(const Line& ray) const {
	return ray.getOrigin();
}

Rect BasicBullet::getBoundingRect() const {
	return Rect();
}

void BasicBullet::draw() {
	this->myine.draw(this->position - this->parent->getRenderer(), NULL, this->angle);
}

void BasicBullet::setImage() {
	this->myine.load("resources/cat.jpg");
	this->myine.scale(11, 5);
}

void BasicBullet::update() {
	this->position += this->mvmt.getValue() * this->delta;
}
