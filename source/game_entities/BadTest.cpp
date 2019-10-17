#include "BadTest.h"

BadTest::BadTest(EnemyDrawGroup* parent, Point position) : EnemyBase(parent, position) {
	this->pathTimer.start();
	/*
	this->c.addPath(new LinePath(Point(-200, 0), toTicks(1)));
	this->c.addPath(new CirclePath(40, 1, Path::SINGLE_LOOP, false));
	this->c.addPath(new LinePath(Point(200, 0), toTicks(1)));
	this->c.addPath(new CirclePath(40, 1, Path::SINGLE_LOOP, false));	
	*/		
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
}

void BadTest::update() {	
	//this->c.update();

	// Temp
	this->accelerate(this->pathFindTo());
	this->move();
}

Point BadTest::getPos() {
	return this->position;
}
