#include "EnemyBase.h"

EnemyBase::EnemyBase(Point position) {
	this->position = position;
	this->texture = new Texture();
}

EnemyBase::~EnemyBase() {
	delete this->texture;
	this->collide = NULL;
}


void EnemyBase::render(Dot* dot) {
	if (this->texture->isLoaded()) {
		this->texture->setPos(this->position);
		this->texture->render(MegaBase::renderer, MegaBase::offset);
	}
}

void EnemyBase::setCollision(CollideBaseGroup* collide) {
	this->collide = collide;
}

void EnemyBase::operator+=(Point delta) {
	float xflag = 0;
	float yflag = 0;
	Point px = delta;
	// Seems really inefficent, investigate it
	if (this->collide != NULL) {
		for (int i = 1; i < 3; i++) {
			if (!xflag) {
				if (collideRectTest(Rect(this->position, this->width, this->height) + px.onlyX() / i, this->collide)) {
					xflag = px.x() / i;
				}
			}
			if (!yflag) {
				if (collideRectTest(Rect(this->position, this->width, this->height) + px.onlyY() / i, this->collide)) {
					yflag = px.y() / i;					
				}
			}
			if (xflag && yflag) {
				break;
			}
		}
	} else {
		xflag = px.x();
		yflag = px.y();
	}
	this->position += Point(xflag, yflag);
	this->angle = atan2(delta.y(), delta.x());
}

std::ostream& operator<<(std::ostream &output, const EnemyBase& base) {
	output << base.position;
	return output;
}
