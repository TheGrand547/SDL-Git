#include "EnemyBase.h"

EnemyBase::EnemyBase(EnemyDrawGroup* parent, Point position) : EntityBase(2.25) {
	this->parent = parent;
	this->position = position;
	this->pathTimer.start();
	
}

EnemyBase::~EnemyBase() {}

void EnemyBase::setParent(EnemyDrawGroup* parent) {
	this->parent = parent;
}

void EnemyBase::draw(SDL_Renderer* renderer, BoundedPoint& offset) {
	if (this->texture.isLoaded()) {
		this->texture.setPos(this->position);
		this->texture.draw(renderer, offset);
	}
	this->standardTimer.tick();
}

Node* EnemyBase::getClosestUnblockedNode() {
	Node* targ = this->parent->nav->getFirst();
	if (this->parent->nav->size() > 1) {
		Point center = this->getCenter();
		for (int i = 1; i < this->parent->nav->size(); i++) {
			float distance = center.distanceToPoint(this->parent->nav->at(i)->getPosition());
			if (distance > 100) {
				continue;
			}
			if (distance < center.distanceToPoint(targ->getPosition())) {
				if (this->parent->collide->doesNotCollideWith(Line(center, this->parent->nav->at(i)->getPosition()))) {
					targ = this->parent->nav->at(i);
				}
			}
		}
	}
	return targ;
}

void EnemyBase::move() {
	// There must be a better way
	float xflag = 0;
	float yflag = 0;
	Point px = this->velocity * this->timer.getRatio();
	if (px.isZero()) {
		return;
	}
	// Seems really inefficent, investigate it
	// Right now it's optimized for non-collision, might want to have some functionality to make it optimized for collision
	if (this->parent->collide != NULL) {
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
	this->angle = atan2(px.y(), px.x());
}

std::ostream& operator<<(std::ostream &output, const EnemyBase& base) {
	output << base.position;
	return output;
}

void EnemyBase::pathFindTo(Point target) {
	if (this->parent->nav != NULL) {
		Point center = this->getCenter();
		if (target.isNull()) {
			target = this->parent->getDot()->getPos();
		}
		if (this->pathTimer.getTicks() > 250) { // If it has been more than 250 milliseconds since the path has been calculated
			this->path = NodePath(this->getClosestUnblockedNode(), target);
			this->pathTimer.start();
		}
		if (this->path.getFirst().isReal()) {
			if (this->path.getFirst().distanceToPoint(center) < 1.5) { // Make the number a constant
				this->path.removeLast();
			}
		}
		Point temp = this->path.getFirst();
		if (temp.isReal()) {
			float angle = atan2(temp.y() - center.y(), temp.x() - center.x());
			this->accelerate(PointDelta(Vector(angle), 1));
		} else {
			this->accelerate(PointDelta(0,0,1));
		}
	}
}
