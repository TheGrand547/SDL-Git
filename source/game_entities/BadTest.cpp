#include "BadTest.h"

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
	return this->parent->collision.doesCollideWith(Rect(this->position, this->width, this->height));
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

void BadTest::draw(SDL_Renderer* renderer, Point offset) {
	if (this->texture.notLoaded()) this->setTexture(renderer);
	EnemyBase::draw(renderer, offset);
	
	/*
	// Draw vision cone - Slopily
	for (int i = -20; i <= 20; i++) {
		Point pTemp = this->getCenter();
		pTemp += 300 * Point(cos(this->angle + radians(i)), sin(this->angle + radians(i)));
		Line temp = Line(this->getCenter(), pTemp);

		Point newTemp = this->parent->collision.closestPointThatCollidesWith(temp);
		if (newTemp.isReal()) {
			temp = Line(this->getCenter(), newTemp);
		}
		temp.setColorChannels(COLORS::BLACK);
		temp.drawLine(this->parent->getRenderer(), this->parent->getOffset());
	}*/
}

void BadTest::setTexture(SDL_Renderer* renderer) {
	this->texture.createBlank(renderer, 50, 50, 0x0000FFFF);
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
