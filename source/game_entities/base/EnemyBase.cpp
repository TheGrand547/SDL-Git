#include "EnemyBase.h"

EnemyBase::EnemyBase(EnemyDrawGroup* parent, Point position) {
	this->parent = parent;
	this->position = position;
	this->texture = new Texture();
}

EnemyBase::~EnemyBase() {
	delete this->texture;
}

void EnemyBase::setParent(EnemyDrawGroup* parent) {
	this->parent = parent;
}

void EnemyBase::draw(SDL_Renderer* renderer, BoundedPoint& offset) {
	if (this->texture->isLoaded()) {
		this->texture->setPos(this->position);
		this->texture->draw(renderer, offset);
	}
	if (this->countedFrames > 1000 || this->countedFrames == 0) {
		this->countedFrames = 0;
		this->timer.start();
	}
	this->countedFrames++;
}

void EnemyBase::move(Point delta) {
	// There must be a better way
	float avg = float(this->countedFrames + 1) / (float(this->timer.getTicks() + 1) / 1000.f);
	float xflag = 0;
	float yflag = 0;
	Point px = delta * (float(Screen::INTENDED_FRAME_RATE) / avg);
	
	if (!px.getNonZero()) {
		return;
	}
	// Seems really inefficent, investigate it
	if (this->parent != NULL) {
		Rect myRect = Rect(this->position, this->width, this->height);
		for (int i = 0; i < 4; i++) {
			Point modified = px / pow(2, i);
			if (!xflag) {
				if (this->parent->collide->doesNotCollideWith(myRect + modified.onlyX())) {
					xflag = modified.x();
				}
			}
			if (!yflag) {
				if (this->parent->collide->doesNotCollideWith(myRect + modified.onlyY())) {
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
