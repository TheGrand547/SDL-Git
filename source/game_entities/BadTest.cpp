#include "BadTest.h"

BadTest::BadTest(Point position) : EnemyBase(position) {
	this->pathTimer.start();
	/*
	this->c->AddPath(new LinePath<EnemyBase>(Point(200, -200), toTicks(1)));
	this->c->AddPath(new CirclePath<EnemyBase>(40, 1, Path<Point>::SINGLE_LOOP, false));
	this->c->AddPath(new LinePath<EnemyBase>(Point(-200, 200), toTicks(1)));
	this->c->AddPath(new CirclePath<EnemyBase>(40, 1, Path<Point>::SINGLE_LOOP, false));			
	this->c->setRepeat(true);
	*/
}

BadTest::BadTest(const BadTest& that) : EnemyBase(that.position) {
	*this = BadTest(that.position);
}

BadTest::~BadTest() {}

bool BadTest::checkLocationValidity() {
	/* True -> Valid location, no collision
	 * False -> Invalid location, collision or some other predefined metric doesn't satisfy */
	return !collideRectTest(this->collide, Rect(this->position, this->width, this->height));
}

void BadTest::setTexture() {
	this->texture->createBlank(MegaBase::renderer, 50, 50, 0xFF0000FF);
}

Node* BadTest::getClosestUnblockedNode() {
	Node* targ = this->nav->getFirst();
	if (this->nav->size() > 1) {
		Point center = this->position + Point() + (Point(this->width, this->height) / 2);
		for (int i = 1; i < this->nav->size(); i++) {
			float distance = center.distanceToPoint(this->nav->at(i)->getPosition());
			if (distance > 100) {
				continue;
			}
			if (distance < center.distanceToPoint(targ->getPosition())) {
				if (checkCollisionBetweenLineAndGroup(this->collide, Line(center, this->nav->at(i)->getPosition()))) {
					targ = this->nav->at(i);
				}
			}
		}
	}
	return targ;
}

void BadTest::draw(Dot* dot) {
	EnemyBase::draw(dot);
	if (this->nav != NULL) {
		Point center = this->position + Point() + (Point(this->width, this->height) / 2); // Maybe function this?
		if (this->pathTimer.getTicks() > 250) { // If it has been more than 250 milliseconds since the path has been calculated
			Node* target = this->getClosestUnblockedNode();
			this->path = NodePath(target, dot->getPos());
			this->pathTimer.start();
		}
		if (this->path.getFirst().isReal()) {
			if (this->path.getFirst().distanceToPoint(center) < 5) { // Make the number a constant
				this->path.removeLast();
			}
		}
		Point temp = this->path.getFirst();
		if (temp.isReal()) {
			float ange = atan2(temp.y() - center.y(), temp.x() - center.x());
			*this += Point(1.5 * cos(ange), 1.5 * sin(ange));
			this->path.draw(center);
		} 
	}
}

void BadTest::update() {
	if (!this->texture->isLoaded()) {
		this->setTexture();
	}
	this->c.update();
}

Point BadTest::getPos() {
	return this->position;
}
