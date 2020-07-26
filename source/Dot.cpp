#include "Dot.h"

Dot::Dot(Point startingCoordinate) : EntityBase(DRAW | MOVEABLE) {
	this->lastDelta = startingCoordinate;
	this->setMaxVelocity(200); // Per second
	this->setFriction(10);
	this->position = BoundedPoint(startingCoordinate, Screen::MAX_WIDTH - Player::PLAYER_X_DIMENSION, Screen::MAX_HEIGHT - Player::PLAYER_Y_DIMENSION);
}

Dot::~Dot() {}

Point Dot::getCenter() {
	return this->position + (Point(Player::PLAYER_X_DIMENSION, Player::PLAYER_Y_DIMENSION) / 2);
}

float Dot::calcAngle(Point point) {
	if (point.y != 0 || point.x != 0) {
		 return atan2(-point.y, point.x);
	}
	return 0;
}

Point Dot::getPosition() const {
	return this->position;
}

Rect Dot::getBoundingRect() const {
	return Rect(this->position, Player::PLAYER_X_DIMENSION, Player::PLAYER_Y_DIMENSION);
}

Line Dot::getRay() {
	Point temp = Point(this->getCenter());
	temp += Point(Player::PLAYER_RAY_CAST_LENGTH * cos(this->angle), Player::PLAYER_RAY_CAST_LENGTH * sin(this->angle));
	return Line(this->getCenter(), temp);
}

float Dot::getAngle() {
	return this->angle;
}

bool Dot::overlap(const Polygon& other) const {
	return this->getBoundingRect().overlap(other);
}

bool Dot::overlap(const std::shared_ptr<ThingBase>& other) const {
	return other->overlap(this->getBoundingRect());
}

bool Dot::wideOverlap(const Polygon& other) const {
	return (this->getBoundingRect() * 1.25).overlap(other);
}

void Dot::draw(SDL_Renderer* renderer, Point offset) {
	SDL_SetRenderDrawColor(renderer, this->r, this->g, this->b, this->a);
	SDL_Rect temp = (this->getBoundingRect() - offset).getSDLRect();
	temp.w = Player::PLAYER_X_DIMENSION;
	temp.h = Player::PLAYER_Y_DIMENSION;
	SDL_RenderFillRect(renderer, &temp);
	Rect p(temp.x, temp.y, Player::PLAYER_X_DIMENSION, Player::PLAYER_Y_DIMENSION);
	p.setColorChannels(0xFF, 0x00, 0x00, 0xFF);
	p.draw(renderer, Point(0,0));
}

void Dot::velocityDelta(Point acceleration) {
	this->EntityBase::accelerate(acceleration.getUnitVector());
}

void Dot::update() {
	this->collideTest();
}

void Dot::collideTest() {
	const int CHECKS = 4;
	
	double tickRatio = this->movement.getValue();
	if (!tickRatio) return;

	Point delta = this->velocity * tickRatio;
	if (delta.isZero()) return;
	
	Point temp = delta / CHECKS;
	PositionLock lock(this->position);
	for (int i = 0; i < CHECKS; i++) {
		this->position += temp;
		if (this->parent->collision.isPositionOpen(this->shared_from_this())) {
			lock.update();
		} else break;
	}
	lock.revert();
	this->lastDelta = lock.delta();
	this->parent->getOffset() += this->lastDelta;
	this->evalAngle(this->lastDelta);
	
	// Zero velocity if it's too small
	if (abs(this->lastDelta.x) < ROUNDING) this->velocity.x = 0;
	if (abs(this->lastDelta.y) < ROUNDING) this->velocity.y = 0;
} 

void Dot::rayCast() {
	Point newPoint = this->parent->collision.closestPointThatCollidesWith(this->getRay());
	if (newPoint.isReal()) {
		Line tempLine = Line(this->getCenter(), newPoint.copy());
		tempLine.setColorChannels(COLORS::CYAN);
		tempLine.drawLine(this->parent->getRenderer(), this->parent->getOffset());
	}
}

bool Dot::doesLineCollide(const Line& ray) const {
	return this->getBoundingRect().doesLineCollide(ray);
}

Point Dot::collideLine(const Line& ray) const {
	return this->getBoundingRect().collideLine(ray);
}
