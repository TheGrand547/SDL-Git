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

void EnemyBase::setCollision(CollideBaseGroup* collide) {
	this->collide = collide;
}

void EnemyBase::move(Point delta) {
	// There must be a better way
	float avg = float(this->countedFrames) / (float(this->timer.getTicks() + 1) / 1000.f);
	float xflag = 0;
	float yflag = 0;
	Point px = delta * (float(Screen::INTENDED_FRAME_RATE) / avg);
	// Seems really inefficent, investigate it
	if (this->collide != NULL) {
		Rect myRect = Rect(this->position, this->width, this->height);
		for (int i = 0; i < 4; i++) {
			Point modified = px / pow(2, i);
			if (!xflag) {
				if (this->collide->doesNotCollideWith(myRect + modified.onlyX())) {
					xflag = modified.x();
				}
			}
			if (!yflag) {
				if (this->collide->doesNotCollideWith(myRect + modified.onlyY())) {
					yflag = modified.y();					
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

void EnemyBase::operator+=(Point delta) {
	this->move(delta);
}

std::ostream& operator<<(std::ostream &output, const EnemyBase& base) {
	output << base.position;
	return output;
}

void EnemyBase::setNavigation(NodeDrawGroup* nav) {
	this->nav = nav;
}
