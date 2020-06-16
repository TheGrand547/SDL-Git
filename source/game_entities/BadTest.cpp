#include "BadTest.h"

BadTest::BadTest(Point position) : EnemyBase(position, DRAW | MOVEABLE) {
	this->maxVelocity = 200;
	this->currentState = State::PATROL;
	
	this->lastPatrolledPoint = Point();
	this->pathTimer.start();
	int dist = 200;
	this->c.addPath(std::make_shared<LinePath>(Point(50, 0), dist, Path::SINGLE_LOOP));
	//this->c.addPath(std::make_shared<ZeroRadiusTurnPath>(0, 200));
	this->c.addPath(std::make_shared<LinePath>(Point(-50, 0), dist, Path::SINGLE_LOOP));
	//this->c.addPath(std::make_shared<ZeroRadiusTurnPath>(M_PI, 200));	
	this->c.setRepeat(true);
}

BadTest::~BadTest() {}

bool BadTest::isLocationInvalid() const {
	/* True  -> Invalid location, collision or some other predefined metric doesn't satisfy
	 * False -> Valid location */
	return this->parent->collision.doesCollideWith(Rect(this->position, this->width, this->height));
}

void BadTest::setTexture(SDL_Renderer* renderer) {
	this->texture.createBlank(renderer, 50, 50, 0xFF0000FF);
}

double BadTest::originDistance() const {
	return this->getRect().getOriginDistance();
}

Point BadTest::getCenter() const {
	return this->position + (Point(this->width, this->height) / 2);
}

void BadTest::draw(SDL_Renderer* renderer, Point offset) {
	if (this->texture.notLoaded()) {
		this->setTexture(renderer);
	}
	EnemyBase::draw(renderer, offset);
	
	if (this->path.getFirst().isReal()) {
		this->path.draw(this->getCenter());
	}
	/*
	// Draw vision cone - Slopily
	
	for (int i = -20; i <= 20; i++) {
		Point pTemp = this->getCenter();
		pTemp += Point(300 * cos(this->angle + radians(i)), 300 * sin(this->angle + radians(i)));
		Line temp = Line(this->getCenter(), pTemp);

		Point newTemp = this->parent->collision.closestPointThatCollidesWith(temp);
		if (newTemp.isReal()) {
			temp = Line(this->getCenter(), newTemp);
		}
		temp.setColorChannels(COLORS::BLACK);
		temp.drawLine(this->parent->getRenderer(), this->parent->getOffset());
	}*/
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
				PointDelta temp = this->pathFindTo(this->targetPoint);
				if (temp.isReal()) {
					this->move(temp);	
				} else {
					this->currentState = State::RETURN;
					this->path.clear();
				}
			}
			break;
		case State::ENGAGE:
			std::cout << "DIE SWINE" << std::endl;
			break;
		case State::RETURN:
			{
				if (this->lastPatrolledPoint.isReal()) {
					PointDelta temp = this->pathFindTo(this->lastPatrolledPoint);
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
	/*
	// SLOPPY
	
	if (this->currentState == State::PATROL || this->currentState == State::GOTO) {
		for (int i = -20; i <= 20; i++) {
			Point pTemp = this->getCenter();
			pTemp += Point(cos(this->angle + radians(i)), sin(this->angle + radians(i))) * 300;
			Line temp = Line(this->getCenter(), pTemp);

			Point newTemp = this->parent->collision.closestPointThatCollidesWith(temp);
			if (newTemp.isReal()) {
				temp = Line(this->getCenter(), newTemp);
			}
			
			if (this->parent->getPlayer()->getRect().doesLineCollide(temp)) {
				this->targetPoint = this->parent->getPlayer()->getPosition();
				if (this->currentState == State::PATROL) {
					//std::cout << "NOW GOTO: " << this->position << std::endl;
					this->lastPatrolledPoint = this->getCenter();
					this->c.pause();
				}
				this->currentState = State::GOTO;
				break;
			}
		}
	}*/
}

Point BadTest::getPosition() const {
	return this->position;
}

Rect BadTest::getRect() const {
	return Rect(this->position, this->width, this->height);
}

bool BadTest::overlap(const Rect& other) const {
	return this->getRect().overlap(other);
}

bool BadTest::overlap(const std::shared_ptr<ThingBase>& other) const {
	return this->overlap(other->getRect());
}

bool BadTest::doesLineCollide(const Line& ray) const {
	return this->getRect().doesLineCollide(ray);
}

Point BadTest::collideLine(const Line& ray) const {
	return this->getRect().collideLine(ray);
}
