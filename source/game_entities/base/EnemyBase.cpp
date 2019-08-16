#include "EnemyBase.h"

EnemyBase::EnemyBase(Point position) {
	this->position = position;
	this->texture = new Texture();
	this->collide = NULL;
	this->nav = NULL;
}

EnemyBase::~EnemyBase() {
	delete this->texture;
}


void EnemyBase::draw(Dot* dot) {
	if (this->texture->isLoaded()) {
		this->texture->setPos(this->position);
		this->texture->draw(MegaBase::renderer, MegaBase::offset);
	}
	if (this->countedFrames > 1000 || this->countedFrames == 0) {
		this->countedFrames = 1;
		this->timer.start();
	}
	this->countedFrames++;
}

void EnemyBase::setCollision(CollideBaseGroup& collide) {
	this->collide = &collide;
}

void EnemyBase::operator+=(Point delta) {
	// There must be a better way
	float avg = float(this->countedFrames) / (float(this->timer.getTicks() + 1) / 1000.f);
	float xflag = 0;
	float yflag = 0;
	Point px = delta * (float(Screen::INTENDED_FRAME_RATE) / avg);
	// Seems really inefficent, investigate it
	if (this->collide != NULL) {
		for (int i = 1; i < 3; i++) {
			if (!xflag) {
				if (collideRectTest(this->collide, Rect(this->position, this->width - 1, this->height - 1) + px.onlyX() / i)) {
					xflag = px.x() / i;
				}
			}
			if (!yflag) {
				if (collideRectTest(this->collide, Rect(this->position, this->width - 1, this->height - 1) + px.onlyY() / i)) {
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

void EnemyBase::setNavigation(NodeDrawGroup& nav) {
	this->nav = &nav;
}
