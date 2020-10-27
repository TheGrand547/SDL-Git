#include "BasicBullet.h"
#include "../GameInstance.h"
#include "../PositionLock.h"

BasicBullet::BasicBullet(Point position, double angle, double speed) : ThingBase(MOVEABLE | DRAW), angle(angle), 
						delta(Point::vectorFromAngle(angle) * speed) {
	this->position = position;
	this->setImage();
	this->calculate();
}

BasicBullet::BasicBullet(Point position, Point delta) : ThingBase(MOVEABLE | DRAW), 
						angle(Point::angleFromVector(delta) * -180.0 / M_PI), delta(delta) {
	this->position = position;
	this->setImage();
	this->calculate();
}

BasicBullet::~BasicBullet() {}

bool BasicBullet::doesLineCollide(const Line& ray) const {
	return ray.isOrthogonal(Line(Point(), Point()));
}

bool BasicBullet::overlap(const Polygon& other) const {
	return this->pain.overlap(other);
}

bool BasicBullet::overlap(const ThingPtr& other) const {
	return other->overlap(this->pain);
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
	return this->pain.getBoundingRect();
}

void BasicBullet::draw() {
	this->myine.drawCentered(this->position - this->parent->getRenderer(), NULL, this->angle * 180 / M_PI);
}

void BasicBullet::setImage() {
	this->myine.load("resources/images/stupid.png");
}

void BasicBullet::calculate() {
	this->pain = Rect(Point(0, 0), Point::vectorFromAngle(this->angle * M_PI / 180.0) * 5, -Point::vectorFromAngle(angle * M_PI / 180.0 + M_PI_2) * 11);
	this->pain.setColorChannels(0xFF, 0x00, 0x00, 0xFF);
	this->pain.setCenter(this->position);
}

void BasicBullet::pingInternal(const std::string& string, const double& data) {
	if (!strcmp("", string.c_str()) && data == 0) {
		this->remove();
	}
}

void BasicBullet::remove() {
	this->parent->queueRemoval(this->shared_from_this());
	if (this->owner) removeValue(this->owner->getMyThings(), this->shared_from_this());
}

void BasicBullet::update() {
	if (!this->pain.overlap(this->parent->getPlayableArea())) this->remove();
	PositionLock lock(this->position);
	this->position += this->mvmt.getValue() * this->delta;
	if (this->parent->collision.isPositionOpen(this->shared_from_this())) {
		lock.update();
	} else {
		this->parent->queueRemoval(this->shared_from_this());
	}
	lock.revert();
	this->pain.setCenter(this->position);
}
