#include "Dot.h"

Dot::Dot(Point startingCoordinate) : EntityBase(4, 1.25) {
	this->flags |= DRAW | MOVEABLE;
	this->position = BoundedPoint(startingCoordinate, 0, 0, Screen::MAX_WIDTH - Player::PLAYER_X_DIMENSION, Screen::MAX_HEIGHT - Player::PLAYER_Y_DIMENSION);
}

Dot::~Dot() {}

Point Dot::getCenter() {
	return this->position + (Point(Player::PLAYER_X_DIMENSION, Player::PLAYER_Y_DIMENSION) / 2);
}

float Dot::calcAngle(Point point) {
	if(point.y() != 0 || point.x() != 0) {
		 return atan2(-point.y(), point.x());
	}
	return 0;
}

void Dot::move(Point delta) {
	this->position += delta;
	evalAngle(delta);
}

Point Dot::getPosition() const {
	return this->position;
}

Rect Dot::getRect() const {
	return Rect(this->position, Player::PLAYER_X_DIMENSION, Player::PLAYER_Y_DIMENSION);
}

Line Dot::getRay() {
	Point temp = Point(this->getCenter());
	temp += Point(Player::PLAYER_RAY_CAST_LENGTH * cos(this->angle), Player::PLAYER_RAY_CAST_LENGTH * sin(this->angle));
	return Line(this->getCenter(), temp);
}

float Dot::getAngle() {
	return this->angle * 180 / M_PI;
}

bool Dot::overlap(const Rect other) const {
	return this->getRect().overlap(other);
}

bool Dot::overlap(const std::shared_ptr<ThingBase>& other) const {
	return this->overlap(other->getRect());
}

void Dot::draw(SDL_Renderer* renderer, Point offset) {
	SDL_SetRenderDrawColor(renderer, rChannel, gChannel, bChannel, aChannel);
	SDL_Rect temp = tempF((this->getRect() - offset)).getSDLRect();
	temp.w = Player::PLAYER_X_DIMENSION;
	temp.h = Player::PLAYER_Y_DIMENSION;
	SDL_RenderFillRect(renderer, &temp);
	Rect p(temp.x, temp.y, Player::PLAYER_X_DIMENSION, Player::PLAYER_Y_DIMENSION);
	p.setColorChannels(0xFF, 0x00, 0x00, 0xFF);
	p.draw(renderer, Point(0,0));
}

void Dot::velocityDelta(PointDelta acceleration) {
	this->EntityBase::accelerate(acceleration);
}

void Dot::update() {
	this->collideTest();
}

void Dot::collideTest() {
	Point delta = this->velocity * this->timer.getRatio();
	if (delta.isZero()) {
		return;
	}
	float xDelta = 0, yDelta = 0;
	for (int i = 0; i < 5; i++) {
		Point temp = delta / pow(2, i);
		if (not xDelta) {
			if (this->parent->collision.doesNotCollideWith(this->getRect() + temp.onlyX())) {
				xDelta = temp.x();
				this->parent->getOffset() += temp.onlyX();
			}
		}
		if (not yDelta) {
			if (this->parent->collision.doesNotCollideWith(this->getRect() + temp.onlyY())) {
				yDelta = temp.y();
				this->parent->getOffset() += temp.onlyY();					
			}
		}
		if (xDelta && yDelta) {
			break;
		}
	}
	// TODO: Make comparison constant
	if (abs(yDelta) < 0.005) {
		this->velocity.yZero();
	}
	if (abs(xDelta) < 0.005) {
		this->velocity.xZero();
	}
	this->move(Vector(xDelta, yDelta));
	this->lastDelta = Point(xDelta, yDelta);
	// PUT THIS ELSEWHERE <- Will be handled when implementation is changed to being based around the Screen Class
	if (this->getPosition().x() < Screen::SCREEN_WIDTH / 2) {
		this->parent->getOffset().xZero();
	}
	if (this->getPosition().y() < Screen::SCREEN_HEIGHT / 2) {
		this->parent->getOffset().yZero();
	}
	
	if (this->getPosition().x() > Screen::MAX_X_SCROLL_DISTANCE) {
		this->parent->getOffset() = Point(Screen::MAX_SCREEN_X_POS, this->parent->getOffset().y());
	}
	if (this->getPosition().y() > Screen::MAX_Y_SCROLL_DISTANCE) {
		this->parent->getOffset() = Point(this->parent->getOffset().x(), Screen::MAX_SCREEN_Y_POS);
	}
} 

void Dot::rayCast() {
	Point newPoint = this->parent->collision.closestPointThatCollidesWith(this->getRay());
	if (newPoint.isReal()) {
		Line tempLine = Line(this->getCenter(), newPoint.copy());
		tempLine.setColorChannelsTo(COLORS::CYAN);
		tempLine.drawLine(MegaBase::renderer, MegaBase::offset);
	}
}

bool Dot::doesLineCollide(const Line& ray) const {
	return this->getRect().doesLineCollide(ray);
}

Point Dot::collideLine(const Line& ray) const {
	return this->getRect().collideLine(ray);
}


// DUMB STUFF, PLEASE IGNORE
/*
int tempF(double val) {
	return int(val) + ((val - int(val) > .005) ? 1 : 0);
}*/

int tempF(double val) {
	return ((val - int(val) > (1 - .05)) ? 1 : 0);
}

Point tempF(Point point) {
	return Point(tempF(point.x()), tempF(point.y()));
}

Rect tempF(Rect rect) {
	rect += tempF(rect.getTopLeft());
	return rect;
}
