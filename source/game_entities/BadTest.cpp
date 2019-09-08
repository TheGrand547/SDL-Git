#include "BadTest.h"
#include "../primitives/Vector.h"

BadTest::BadTest(EnemyDrawGroup* parent, Point position) : EnemyBase(parent, position) {
	this->pathTimer.start();
	/*
	this->c.AddPath(new LinePath<EnemyBase>(Point(200, -200), toTicks(1)));
	this->c.AddPath(new CirclePath<EnemyBase>(40, 1, Path<Point>::SINGLE_LOOP, false));
	this->c.AddPath(new LinePath<EnemyBase>(Point(-200, 200), toTicks(1)));
	this->c.AddPath(new CirclePath<EnemyBase>(40, 1, Path<Point>::SINGLE_LOOP, false));			
	this->c.setRepeat(true);
	*/
}

BadTest::BadTest(const BadTest& that) : EnemyBase(that.parent, that.position) {
	*this = BadTest(that.parent, that.position);
}

BadTest::~BadTest() {}

bool BadTest::isLocationInvalid() {
	/* True ->  Invalid location, collision or some other predefined metric doesn't satisfy
	 * False -> Valid location */
	return this->parent->collide->doesCollideWith(Rect(this->position, this->width, this->height));
}

void BadTest::setTexture() {
	this->texture->createBlank(MegaBase::renderer, 50, 50, 0xFF0000FF);
}

Point BadTest::getCenter() {
	return this->position + Point() + (Point(this->width, this->height) / 2);
}

Node* BadTest::getClosestUnblockedNode() {
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

void BadTest::draw(Dot* dot) {
	EnemyBase::draw(dot);
	if (this->parent->nav != NULL) {
		Point center = this->getCenter();
		if (this->pathTimer.getTicks() > 250) { // If it has been more than 250 milliseconds since the path has been calculated
			this->path = NodePath(this->getClosestUnblockedNode(), dot->getPos());
			this->pathTimer.start();
		}
		if (this->path.getFirst().isReal()) {
			if (this->path.getFirst().distanceToPoint(center) < 5) { // Make the number a constant
				this->path.removeLast();
			}
		}
		Point temp = this->path.getFirst();
		if (temp.isReal()) {
			float angle = atan2(temp.y() - center.y(), temp.x() - center.x());
			this->move(Vector(angle) * 2.25);
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
