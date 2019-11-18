#include "BadTest.h"

BadTest::BadTest(EnemyDrawGroup* parent, Point position) : EnemyBase(parent, position) {
	this->currentState = State::PATROL;
	
	this->lastPatrolledPoint = Point();
	this->pathTimer.start();
	
	this->c.addPath(new LinePath(PointDelta(-1.5, 0, 1.5), 200, Path::SINGLE_LOOP));
	//this->c.addPath(new CirclePath(40, 1, Path::SINGLE_LOOP, false));
	this->c.addPath(new LinePath(PointDelta(1.5, 0, 1.5), 200, Path::SINGLE_LOOP));
	//this->c.addPath(new CirclePath(40, 1, Path::SINGLE_LOOP, false));	
	
	this->c.setRepeat(true);
}

BadTest::BadTest(const BadTest& that) : EnemyBase(that.parent, that.position) {
	*this = BadTest(that.parent, that.position);
}

BadTest::~BadTest() {}

bool BadTest::isLocationInvalid() {
	/* True  -> Invalid location, collision or some other predefined metric doesn't satisfy
	 * False -> Valid location */
	return this->parent->collide->doesCollideWith(Rect(this->position, this->width, this->height));
}

void BadTest::setTexture(SDL_Renderer* renderer) {
	this->texture.createBlank(renderer, 50, 50, 0xFF0000FF);
}

Point BadTest::getCenter() {
	return this->position + (Point(this->width, this->height) / 2);
}

void BadTest::draw(SDL_Renderer* renderer, BoundedPoint& offset) {
	if (this->texture.notLoaded()) {
		this->setTexture(renderer);
	}
	EnemyBase::draw(renderer, offset);
	if (this->path.getFirst().isReal()) {
		this->path.draw();
	}
	// Draw vision cone - Slopily
	/*
	for (int i = -20; i <= 20; i++) {
		Point pTemp = this->getCenter();
		pTemp += Point(300 * cos(this->angle + radians(i)), 300 * sin(this->angle + radians(i)));
		Line temp = Line(this->getCenter(), pTemp);

		Point newTemp = this->parent->collide->closestPointThatCollidesWith(temp);
		if (newTemp.isReal()) {
			temp = Line(this->getCenter(), newTemp);
		}
		temp.setColorChannels(COLORS::BLACK);
		temp.drawLine(MegaBase::renderer, MegaBase::offset);
	}*/
}

void BadTest::update() {
	// This test AI will be based on a Finite State Machine
	//this->c.update();

	// Temp
	
	switch (this->currentState) {
		case State::PATROL:
			if (this->c.paused()) {
				this->c.unpause();
			}
			this->c.update();
			break;
		case State::STANDBY:
			break;
		case State::GOTO: 
			{
				PointDelta temp = this->pathFindTo(this->targetPoint);
				if (temp.getNonZero()) {
					this->accelerate(temp);	
				} else {
					//std::cout << "NOW RETURN TO: " << this->lastPatrolledPoint << std::endl;
					this->currentState = State::RETURN;
					this->path.clear();
				}
			}
			break;
		case State::ENGAGE:
			this->accelerate(PointDelta(0, 0, 0));
			break;
		case State::RETURN:
			{
				if (this->lastPatrolledPoint.isReal()) {
					PointDelta temp = this->pathFindTo(this->lastPatrolledPoint);
					if (temp.getNonZero()) {
						this->accelerate(temp);
					} else {
						//std::cout << "NOW PATROL: " << this->position << std::endl;
						this->currentState = State::PATROL;
					}
				} else {
					this->currentState = State::ERROR;
				}
			}
			break;
		case State::ERROR:
			// TODO: Add debug logger
			std::cout << "fa" << std::endl;
			break;
	}
	// SLOPPY
	if (this->currentState == State::PATROL || this->currentState == State::GOTO) {
		for (int i = -20; i <= 20; i++) {
			Point pTemp = this->getCenter();
			pTemp += Point(cos(this->angle + radians(i)), sin(this->angle + radians(i))) * 300;
			Line temp = Line(this->getCenter(), pTemp);

			Point newTemp = this->parent->collide->closestPointThatCollidesWith(temp);
			if (newTemp.isReal()) {
				temp = Line(this->getCenter(), newTemp);
			}
			if (this->parent->getDot()->getRect().doesLineCollide(temp)) {
				this->targetPoint = this->parent->getDot()->getPos();
				if (this->currentState == State::PATROL) {
					//std::cout << "NOW GOTO: " << this->position << std::endl;
					this->lastPatrolledPoint = this->getCenter();
					this->c.pause();
				}
				this->currentState = State::GOTO;
				break;
			}
		}
	}
	this->move();
}

Point BadTest::getPos() {
	return this->position;
}
