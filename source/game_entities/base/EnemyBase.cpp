#include "EnemyBase.h"

EnemyBase::EnemyBase(Point position, int flags) : ThingBase(flags | DRAW), maxVelocity(2.5) {
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

void EnemyBase::move(Point velocity) { // TODO: Maybe re-write this under a different name?
	// There must be a better way
	double gp = this->mvmnt.getValue();
	if (velocity.getMagnitude() > this->maxVelocity) {
		velocity = velocity.getUnitVector() * this->maxVelocity;
	}
	Point px = velocity * gp;
	if (px.isZero()) {
		return;
	}
	// Seems really inefficent, investigate it
	// Right now it's optimized for non-collision, might want to have some functionality to make it optimized for collision
	double xflag = 0, yflag = 0;
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


