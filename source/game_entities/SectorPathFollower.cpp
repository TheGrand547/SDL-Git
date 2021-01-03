#include "SectorPathFollower.h"
#include "../essential/MathUtils.h"
#include "../wrappers/AlertText.h"
#include "../wrappers/LinkedText.h"
#include "../GameInstance.h"
#include "BasicBullet.h"

SectorPathFollower::SectorPathFollower(Rect rect) : ThingBase(DRAW | MOVEABLE), seen(0), box(rect), mine(this) {}

SectorPathFollower::~SectorPathFollower() {}

bool SectorPathFollower::doesLineCollide(const Line& ray) const {
	return this->box.doesLineCollide(ray);
}

bool SectorPathFollower::isAlive() const {
	return !this->parent->getPlayer()->overlap(this->box);
}

bool SectorPathFollower::overlap(const Polygon& other) const {
	return this->box.overlap(other);
}

bool SectorPathFollower::overlap(const std::shared_ptr<ThingBase>& other) const {
	return other->overlap(this->box);
}

double SectorPathFollower::originDistance() const {
	return this->box.getCenter().distanceToPoint();
}

Point SectorPathFollower::collideLine(const Line& ray) const {
	return this->box.collideLine(ray);
}

Point SectorPathFollower::getPosition() const {
	return this->box.getTopLeft();
}


Rect SectorPathFollower::getBoundingRect() const {
	return this->box;
}

void SectorPathFollower::draw() {
	if (!this->texture.isLoaded()) {
		this->texture.load("resources/images/temp.png");
		this->texture.scale(this->box.getWidth(), this->box.getHeight());
	}
	this->mine.draw();
	this->texture.draw(this->getPosition() - this->parent->getRenderer());
	int angle = this->getAngle() * 180.0 / M_PI;
	Point p = (this->box.getCenter() - this->parent->getRenderer()).offset;
	filledPieRGBA(this->parent->getRenderer().renderer, (int) p.x, (int) p.y, 200, angle - 20, angle + 20, 0x00, 0x00, 0x00, 0x40);
	filledPieRGBA(this->parent->getRenderer().renderer, (int) p.x, (int) p.y, 100, angle - 40, angle + 40, 0x00, 0x00, 0x00, 0x40);
}

void SectorPathFollower::update() {
	if (!this->created)  {
		this->created = true;
		this->parent->createText<LinkedText<int>>(Point(500, 100), this->seen);
	}
	for (const ThingPtr& thing: this->parent->getPlayer()->getMyThings()) {
		if (thing->overlap(this->box)) {
			this->parent->queueRemoval(this->shared_from_this());
			thing->ping();
			break;
		}
	}
	Point p12 = this->box.getCenter();
	Point pp2 = this->parent->getPlayer()->getBoundingRect().getCenter();
	// TODO: Make sure this is relatively accurate instead of rarely accurate
	int ticks = this->timer.getTicks();
	if (p12.distanceToPoint(pp2) < 150 && abs(Math::angleBetween(p12, pp2) - this->angle) < (20 * M_PI / 180.0)) {
		this->seen += ticks;
		if (this->seen > 750) {
			this->seen = 0;
			this->parent->createText<AlertText>("Spotted a dumbo :D", p12, Colors::Red, 2500);
		}
		// this->createOwnedThing<BasicBullet>(p12, this->angle, 500);
	} else {
		this->seen = (this->seen > ticks) ? this->seen - (ticks * .25) : 0;
	}
	this->timer.start();
	Point p = this->mine.currentTarget(this->box.getCenter());
	double value = this->movement.getValue();
	if (p.isNull() || !value) return;
	this->box += p * value * 100;
	if (CollisionHandler::locationValid(this->shared_from_this())) {
		this->setAngle(p);
	} else {
		// Don't move, but removed cause that's not relevant to current testing
		//LOG("I'm stuck at (%f, %f)", this->box.getCenter().x, this->box.getCenter().y);
		//this->box -= p * value * 100;
	}
	this->parent->gameState["PathFinished"] = (int) this->mine.isFinished();
}
