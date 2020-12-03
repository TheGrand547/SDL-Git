#include "Dot.h"
#include "essential/constants.h"
#include "essential/MathUtils.h"
#include "essential/util.h"
#include "game_entities/BasicBullet.h"
#include "GameInstance.h"
#include "PositionLock.h"

Dot::Dot(Point startingCoordinate) : EntityBase(DRAW | MOVEABLE) {
	this->surface.load("resources/images/cat.jpg");
	this->surface.scale(Player::xDimension, Player::yDimension);
	this->lastDelta = startingCoordinate;
	this->setMaxVelocity(200); // Per second
	this->setFriction(10);
	this->position = BoundedPoint(startingCoordinate, Screen::maxWidth - Player::xDimension, Screen::maxHeight - Player::yDimension);
}

Dot::~Dot() {}

Point Dot::getCenter() {
	return this->position + (Point(Player::xDimension, Player::yDimension) / 2);
}

bool Dot::overlap(const Polygon& other) const {
	return this->getBoundingRect().overlap(other);
}

bool Dot::overlap(const std::shared_ptr<ThingBase>& other) const {
	return other->overlap(this->getBoundingRect());
}

bool Dot::doesLineCollide(const Line& ray) const {
	return this->getBoundingRect().doesLineCollide(ray);
}

double Dot::calcAngle(Point point) {
	if (point.getNonZero()) return atan2(-point.y, point.x);
	return 0;
}

Point Dot::getPosition() const {
	return this->position;
}

Line Dot::getRay() {
	Point temp = Point(this->getCenter());
	temp += Player::rayCastLength * Point::vectorFromAngle(this->angle);
	return Line(this->getCenter(), temp);
}

Rect Dot::getBoundingRect() const {
	return Rect(this->position, Player::xDimension, Player::yDimension);
}

Point Dot::collideLine(const Line& ray) const {
	return this->getBoundingRect().collideLine(ray);
}

void Dot::collideTest() {
	const int CHECKS = 4; // Probably put this somewhere else...

	Point delta = this->velocity * this->mvmt.getValue();
	if (delta.isZero()) return;

	Point temp = delta / CHECKS;
	PositionLock lock(this->position);
	for (int i = 0; i < CHECKS; i++) {
		// TODO: Increase velocity of the other section so that the other velocity is boosted slightly when going diagonally
		// TODO: Feels sloppy as shit
		if (temp.isZero()) break;
		this->position += temp.onlyX();
		if (this->parent->collision.isPositionOpen(this->shared_from_this())) {
			lock.update();
		} else {
			temp.x = 0;
			lock.revert();
		}
		this->position += temp.onlyY();
		if (this->parent->collision.isPositionOpen(this->shared_from_this())) {
			lock.update();
		}  else {
			temp.y = 0;
			lock.revert();
		}
	}
	lock.revert();
	if (lock.delta().isZero()) {
		// Diagonal Check
		for (int i = 0; i < CHECKS; i++) {
			this->position += temp;
			if (this->parent->collision.isPositionOpen(this->shared_from_this())) {
				lock.update();
			} else break;
		}
		lock.revert();
	}
	this->lastDelta = lock.delta();
	this->parent->getOffset() += this->lastDelta;
	this->evalAngle(this->lastDelta);

	// Zero velocity if it's too small
	if (std::abs(this->lastDelta.x) < ROUNDING) this->velocity.x = 0;
	if (std::abs(this->lastDelta.y) < ROUNDING) this->velocity.y = 0;
} 

void Dot::draw() {
	this->surface.draw(this->position - this->parent->getRenderer());
}

void Dot::rayCast() {
	Point newPoint = this->parent->collision.closestPointThatCollidesWith(this->getRay());
	if (newPoint.isReal()) {
		Line tempLine = Line(this->getCenter(), newPoint.copy());
		tempLine.setColorChannels(Colors::Cyan);
		tempLine.draw(this->parent->getRenderer());
	}
}

void Dot::shoot() {
	double ang = Math::radians((((int) Math::degrees(this->angle)) / 45) * 45);
	std::cout << ang << std::endl;
	//this->createOwnedThing<BasicBullet>(this->getBoundingRect().getCenter(), ang, 500);
}

void Dot::update() {
	this->EntityBase::accelerate({this->parent->gameState["p_x"], this->parent->gameState["p_y"]});
	this->parent->gameState["p_x"] = 0;
	this->parent->gameState["p_y"] = 0;
	this->collideTest();
}
