#include "EnemyBase.h"

EnemyBase::EnemyBase(Point position, int flags) : ThingBase(flags | DRAW), maxVelocity(200) {
	this->position = position;
	this->timer.start();
	this->pathTimer.start();
}

EnemyBase::~EnemyBase() {}

void EnemyBase::draw(SDL_Renderer* renderer, Point offset) {
	if (this->texture.isLoaded()) {
		this->texture.draw(renderer, this->position - offset);
	}
}

void EnemyBase::move(Point velocity) { 
	double tickRatio = this->movement.getValue();
	if (!tickRatio) return;
	Point px = velocity.getUnitVector() * tickRatio * this->maxVelocity;
	
	// Seems really inefficent, investigate it
	// Right now it's optimized for non-collision, might want to have some functionality to make it optimized for collision
	double xflag = 0, yflag = 0;
	if (this->parent->collision.size() > 0) {
		Rect myRect = Rect(this->position, this->width, this->height);
		for (int i = 0; i < 4; i++) {
			Point modified = px / pow(2, i);
			if (not xflag) {
				if (this->parent->collision.doesNotCollideWith(myRect + modified.onlyX())) {
					xflag = modified.x;
				}
			}
			if (not yflag) {
				if (this->parent->collision.doesNotCollideWith(myRect + modified.onlyY())) {
					yflag = modified.y;
				}
			}
			if (xflag && yflag) {
				break;
			}
		}
	} else {
		xflag = px.x;
		yflag = px.y;
	}
	this->position += Point(xflag, yflag);
	if (!this->turning) {
		this->angle = atan2(px.y, px.x);
	}
}

std::ostream& operator<<(std::ostream& output, const EnemyBase& base) {
	output << base.position;
	return output;
}

Point EnemyBase::pathFindTo(Point target) {
	return target * 2;
}

void EnemyBase::turn(double delta) {
	if (this->turning) {
		this->angle += delta;
	}
}

void EnemyBase::toggleTurn() {
	this->turning = !this->turning;
}

double EnemyBase::getAngle() const {
	return this->angle;
}


