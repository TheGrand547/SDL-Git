#include "BadTest.h"

BadTest::BadTest(Point position) : EnemyBase(position) {
	this->c = new PathManager<EnemyBase>(this);
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

BadTest::~BadTest() {
	delete this->c;
}

bool BadTest::checkLocationValidity() {
	/* True -> Valid location, no collision
	 * False -> Invalid location, collision or some other predefined metric doesn't satisfy */
	return !collideRectTest(this->collide, Rect(this->position, this->width, this->height));
}

void BadTest::set() {
	this->texture->createBlank(MegaBase::renderer, 50, 50, 0xFF0000FF);
}

Node* BadTest::getClosestUnblockedNode() {
	Node* targ = (*this->nav)[0];
	Point center = this->position + Point() + (Point(this->width, this->height) / 2);
	if (this->nav->size() > 1) {
		for (int i = 1; i < this->nav->size(); i++) {
			if (!checkCollisionBetweenLineAndGroup(this->collide, Line(center, (*this->nav)[i]->getPosition()))) {
				continue;
			}
			if (center.distanceToPoint((*this->nav)[i]->getPosition()) < center.distanceToPoint(targ->getPosition())) {
				targ = (*this->nav)[i];
			}
		}
	}
	return targ;
}

void BadTest::draw(Dot* dot) {
	EnemyBase::draw(dot);
	if (this->nav != NULL) {
		Point center = this->position + Point() + (Point(this->width, this->height) / 2); // Maybe function this?
		if (this->path.getFirst().isReal()) {
			if (this->path.getFirst().distanceToPoint(center) < 5) { // Make the number a constant
				Node* target = this->getClosestUnblockedNode();
				if (target->getPosition() != this->path.getFirst()) {
					NodePath temp = NodePath(target, dot->getPos());
					if (this->path.distance() - temp.distance() > 150) { // If the new path is more than 150 pixels more efficent
						this->path = temp;
					}
				} else { // As the distance is less than 5, we should instead remove the last element
					this->path.removeLast();
				}
			}
		} else { // If there is no path, generate one
			Node* target = this->getClosestUnblockedNode();
			this->path = NodePath(target, dot->getPos());
		}
		Point temp = this->path.getFirst();
		if (temp.isReal()) {
			float ange = atan2(temp.y() - center.y(), temp.x() - center.x());
			*this += Point(3 * cos(ange), 3 * sin(ange));
			this->path.draw();
		} 
	}
}

void BadTest::update() {
	if (!this->texture->isLoaded()) {
		this->set();
	}
	this->c->update();
}

Point BadTest::getPos() {
	return this->position;
}
