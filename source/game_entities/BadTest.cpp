#include "BadTest.h"
#include "../essential/misc.h"
#include "../wrappers/Timer.h"
#include "../wrappers/Texture.h"
#include "../GameInstance.h"
#include "paths/CirclePath.h"
#include "paths/LinePath.h"
#include "paths/ZeroRadiusTurnPath.h"
#include "CollisionHandler.h"
#include <math.h>
#include <SDL.h>

BadTest::BadTest(Point position) : EnemyBase(position, DRAW | MOVEABLE) {
	this->maxVelocity = 150;
	this->currentState = State::PATROL;

	this->lastPatrolledPoint = Point();
	this->pathTimer.start();
	int dist = 200;
	this->c.addPath(std::make_shared<LinePath>(Point(50, 0), dist, Path::SINGLE_LOOP));
	this->c.addPath(std::make_shared<LinePath>(Point(-50, 0), dist, Path::SINGLE_LOOP));
	this->c.setRepeat(true);
}

BadTest::~BadTest() {}

bool BadTest::doesLineCollide(const Line& ray) const {
	return this->getBoundingRect().doesLineCollide(ray);
}

bool BadTest::isLocationInvalid() const {
	/* True  -> Invalid location, collision or some other predefined metric doesn't satisfy
	 * False -> Valid location */
	return this->parent->collision->doesCollideWith(Rect(this->position, this->width, this->height));
}

bool BadTest::overlap(const Polygon& other) const {
	return this->getBoundingRect().overlap(other);
}

bool BadTest::overlap(const std::shared_ptr<ThingBase>& other) const {
	return other->overlap(this->getBoundingRect());
}

double BadTest::originDistance() const {
	return this->getBoundingRect().getOriginDistance();
}

Point BadTest::collideLine(const Line& ray) const {
	return this->getBoundingRect().collideLine(ray);
}

Point BadTest::getCenter() const {
	return this->position + (Point(this->width, this->height) / 2);
}

Point BadTest::getPosition() const {
	return this->position;
}

Rect BadTest::getBoundingRect() const {
	return Rect(this->position, this->width, this->height);
}

void BadTest::draw() {
	if (this->texture.notLoaded()) this->setTexture();
	EnemyBase::draw();
}

void BadTest::setTexture() {
	this->texture.createBlank(this->parent->getTrueRenderer(), 50, 50, 0x0000FFFF);
}


void BadTest::update() {
	// TODO: Switch to only one move() call per frame
	this->timer.tick();
	// This test AI will be based on a Finite State Machine
	
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
				Point temp = this->pathFindTo(this->targetPoint);
				if (temp.isReal()) {
					this->move(temp);	
				} else {
					this->currentState = State::RETURN;
				}
			}
			break;
		case State::ENGAGE:
			std::cout << "DIE SWINE" << std::endl;
			break;
		case State::RETURN:
			{
				if (this->lastPatrolledPoint.isReal()) {
					Point temp = this->pathFindTo(this->lastPatrolledPoint);
					if (temp.getNonZero()) {
						this->move(temp);
					} else {
						this->currentState = State::PATROL;
					}
				} else {
					this->currentState = State::ERROR;
				}
			}
			break;
		case State::ERROR:
			LOG("ERROR: BadTest has entered the ERROR State.");
			break;
	}
}
