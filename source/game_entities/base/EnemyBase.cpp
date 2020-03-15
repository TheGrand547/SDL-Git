#include "EnemyBase.h"

EnemyBase::EnemyBase(Point position) : EntityBase(2.25) {
	this->flags |= DRAW;
	this->position = position;
	this->pathTimer.start();
}

EnemyBase::~EnemyBase() {}

void EnemyBase::draw(SDL_Renderer* renderer, Point offset) {
	if (this->texture.isLoaded()) {
		this->texture.setPos(this->position);
		this->texture.draw(renderer, offset);
	}
}

std::shared_ptr<Node> EnemyBase::getClosestUnblockedNode() {
	std::shared_ptr<Node> targ = this->parent->nodes.getFirst();
	if (this->parent->nodes.size() > 1) {
		Point center = this->getCenter();
		for (int i = 1; i < this->parent->nodes.size(); i++) {
			double distance = center.distanceToPoint(this->parent->nodes.at(i)->getPosition());
			if (distance > 100) {
				continue;
			}
			if (distance < center.distanceToPoint(targ->getPosition())) {
				if (this->parent->collision.doesNotCollideWith(Line(center, this->parent->nodes.at(i)->getPosition()))) {
					targ = this->parent->nodes.at(i);
				}
			}
		}
	}
	return targ;
}

void EnemyBase::move() { // TODO: Maybe re-write this under a different name?
	// There must be a better way
	double xflag = 0;
	double yflag = 0;
	Point px = this->velocity * this->timer.getRatio();
	
	if (px.isZero()) {
		return;
	}
	// Seems really inefficent, investigate it
	// Right now it's optimized for non-collision, might want to have some functionality to make it optimized for collision
	if (this->parent->collision.size() > 0) {
		Rect myRect = Rect(this->position, this->width, this->height);
		for (int i = 0; i < 4; i++) {
			Point modified = px / pow(2, i);
			if (not xflag) {
				if (this->parent->collision.doesNotCollideWith(myRect + modified.onlyX())) {
					xflag = modified.x();
				}
			}
			if (not yflag) {
				if (this->parent->collision.doesNotCollideWith(myRect + modified.onlyY())) {
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
	if (abs(yflag) < 0.000001) {
		this->velocity.yZero();
	}
	if (abs(xflag) < 0.000001) {
		this->velocity.xZero();
	}
	this->position += Point(xflag, yflag);
	if (!this->turning) {
		this->angle = atan2(px.y(), px.x());
	}
}

std::ostream& operator<<(std::ostream& output, const EnemyBase& base) {
	output << base.position;
	return output;
}

PointDelta EnemyBase::pathFindTo(Point target) {
	if (this->parent->nodes.size() > 0 && target.isReal()) {
		Point center = this->getCenter();
		if (this->pathTimer.getTicks() > 250 || this->path.getFirst().isNull()) { 
			// If it has been more than 250 milliseconds since the path has been calculated
			this->path = NodePath(this->getClosestUnblockedNode(), target);
			this->pathTimer.start();
		} 
		if (this->path.getFirst().isReal()) {
			if (this->path.getFirst().distanceToPoint(center) < 2.5) { // Make the number a constant
				this->path.removeLast();
			}
		}
		Point temp = this->path.getFirst();
		if (temp.isReal()) {
			double angle = atan2(temp.y() - center.y(), temp.x() - center.x());
			return PointDelta(Vector(angle), .75);
		} else {
			if (center.distanceToPoint(target) > 2) {
				double angle = atan2(target.y() - center.y(), target.x() - center.x());
				return PointDelta(Vector(angle), .75);
			}
		}
	}
	return PointDelta(0, 0, 0);
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


