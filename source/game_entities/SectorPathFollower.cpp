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
	filledPieRGBA(this->parent->getRenderer().renderer, (int) p.x, (int) p.y, 200, angle - VISION_SHALLOW, angle + VISION_SHALLOW, 0x00, 0x00, 0x00, 0x40);
	filledPieRGBA(this->parent->getRenderer().renderer, (int) p.x, (int) p.y, 200, angle - VISION_WIDE, angle + VISION_WIDE, 0x00, 0x00, 0x00, 0x40);
}

void SectorPathFollower::update() {
	// Testing thingy
	if (!this->created)  {
		this->created = true;
		//this->parent->createText<LinkedText<int>>(Point(500, 100), this->seen);
	}
	// Bullet Collision
	for (const ThingPtr& thing: this->parent->getPlayer()->getMyThings()) {
		if (thing->overlap(this->box)) {
			this->parent->queueRemoval(this->shared_from_this());
			thing->ping();
			break;
		}
	}
	// TODO: Add decacy of seen even if in ai state
	Point myCenter = this->box.getCenter();
	Point playerCenter = this->parent->getPlayer()->getBoundingRect().getCenter();
	if (!this->parent->gameState["PlayerSpotted"]) {
		double difference = abs(Math::angleBetween(myCenter, playerCenter) - this->angle);
		int ticks = this->timer.getTicks();
		if (myCenter.distanceToPoint(playerCenter) < VISION_RANGE && difference < (VISION_WIDE * M_PI / 180.0) 
			&& CollisionHandler::closestPointThatCollidesWith(NULL, Line(myCenter, playerCenter)).isNull()) {
			if (difference < (VISION_SHALLOW * M_PI / 180.0)) this->seen += ticks;
			this->seen += ticks;
			if (this->seen > 1500) {
				this->parent->gameState["PlayerSpotted"] = 1;
				this->parent->gamePoints["PlayerSpotted"] = playerCenter;
				this->mine.createPath(myCenter, playerCenter);
				this->parent->createText<AlertText>("Spotted a dumbo :D", myCenter - Point(50, 50), Colors::Red, 1000);
			}
		} else {
			this->seen = (this->seen > ticks) ? this->seen - (ticks * .5) : 0;
		}
	} else {
		if (this->mine.size() == 0) {
			this->mine.createPath(myCenter, this->parent->gamePoints["PlayerSpotted"]);
		}
	}
	this->timer.start();

	// Movement
	Point p = this->mine.currentTarget(this->box.getCenter());
	double value = this->movement.getValue();
	if (p.isNull() || !value) return;
	this->box += p * value * 100;
	if (CollisionHandler::locationValid(this->shared_from_this()), SUPER_MOVEMENT) {
		this->setAngle(p);
	} else {
		// Don't move, but removed cause that's not relevant to current testing
		LOG("I'm stuck at (%f, %f)", this->box.getCenter().x, this->box.getCenter().y);
		this->box -= p * value * 100;
	}
	this->parent->gameState["PathFinished"] = (int) this->mine.isFinished();
}
