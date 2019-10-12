#include "Dot.h"

Dot::Dot(Point startingCoordinate) {
	this->angle = 0;
	this->acceleration = Point(0, 0);
	this->velocity = PointDelta(0, 0, 4); // TODO: Make a constant
	this->position = BoundedPoint(startingCoordinate, 0, 0, Screen::MAX_WIDTH - Player::PLAYER_X_DIMENSION, Screen::MAX_HEIGHT - Player::PLAYER_Y_DIMENSION);
}

Dot::~Dot() {}

Point Dot::getCenter() {
	return this->position + Point(Player::PLAYER_X_DIMENSION / 2, Player::PLAYER_Y_DIMENSION / 2);
}

void Dot::evalAngle(Point delta) {
	this->angle = atan2(delta.y(), delta.x());
}

float Dot::calcAngle(Point point) {
	if(point.y() != 0 || point.x() != 0) {
		 return atan2(0-point.y(), point.x());
	}
	return 0;
}

void Dot::move(Point delta) {
	this->position += delta;
	evalAngle(delta);
}

Point Dot::getPos() {
	return this->position;
}

Rect Dot::getRect() {
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

void Dot::draw() {
	SDL_SetRenderDrawColor(MegaBase::renderer, rChannel, gChannel, bChannel, aChannel);
	SDL_Rect temp = (this->getRect() - MegaBase::offset).getSDLRect();
	temp.w = Player::PLAYER_X_DIMENSION;
	temp.h = Player::PLAYER_Y_DIMENSION;
	SDL_RenderFillRect(MegaBase::renderer, &temp);
	Rect p(this->position, Player::PLAYER_X_DIMENSION, Player::PLAYER_Y_DIMENSION);
	p.setColorChannels(0xFF, 0x00, 0x00, 0xFF);
	p.draw(MegaBase::renderer, MegaBase::offset);
}

void Dot::update(PointDelta acceleration) {
	if (acceleration.getMagnitude() < 0.1) {
		acceleration = this->velocity / -10.0;
	}
	this->acceleration = acceleration * this->f->getRatio();
	this->velocity += this->acceleration;
	this->collideTest();
}

void Dot::collideTest() {
	Point delta = this->velocity * this->f->getRatio();
	if (!delta.getNonZero()) {
		return;
	}
	float xDelta = 0;
	float yDelta = 0;
	for (int i = 0; i < 5; i++) {
		Point temp = delta / pow(2, i);
		if (!xDelta) {
			if (this->collision->doesPlayerNotCollide(this->getRect() + temp.onlyX())) {
				xDelta = temp.x();
				*MegaBase::offset += temp.onlyX();
			}
		}
		if (!yDelta) {
			if (this->collision->doesPlayerNotCollide(this->getRect() + temp.onlyY())) {
				yDelta = temp.y();
				*MegaBase::offset += temp.onlyY();					
			}
		}
		if (xDelta && yDelta) {
			break;
		}
	}
	this->move(Vector(xDelta, yDelta));
	// PUT THIS ELSEWHERE <- Will be handled when implementation is changed to being based around the Screen Class
	if (this->getPos().x() < Screen::SCREEN_WIDTH / 2) {
		MegaBase::offset->xZero();
	}
	if (this->getPos().y() < Screen::SCREEN_HEIGHT / 2) {
		MegaBase::offset->yZero();
	}
	if (this->getPos().y() > Screen::MAX_Y_SCROLL_DISTANCE) {
		MegaBase::offset->maxY();
	}
	if (this->getPos().x() > Screen::MAX_X_SCROLL_DISTANCE) {
		MegaBase::offset->maxX();
	}
} 

void Dot::rayCast() {
	Point newPoint = this->collision->closestPointThatCollidesWith(this->getRay());
	if (newPoint.isReal()) {
		Line tempLine = Line(this->getCenter(), newPoint.copy());
		tempLine.setColorChannels(COLORS::CYAN);
		tempLine.drawLine(MegaBase::renderer, MegaBase::offset);
	}
}

void Dot::setCollision(CollideBaseGroup& boxes) {
	this->collision = &boxes;
}
void Dot::setTimer(FpsText& f) {
	this->f = &f;
}
