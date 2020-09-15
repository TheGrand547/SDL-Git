#include "BasicBullet.h"

// TODO: Actually implement these

BasicBullet::BasicBullet(double angle, double speed) : delta(Point::vectorFromAngle(angle) * speed) {}

BasicBullet::BasicBullet(Point delta) : delta(delta) {}

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
	return 0;
}
Point BasicBullet::getPosition() const {
	return Point(0, 0);
}

Point BasicBullet::collideLine(const Line& ray) const {
	return ray.getOrigin();
}

Rect BasicBullet::getBoundingRect() const {
	return Rect();
}

void BasicBullet::draw() {}

void BasicBullet::update() {}
