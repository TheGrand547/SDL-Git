#include "EnemyBase.h"
#include "../../essential/constants.h"
#include "../../PositionLock.h"
#include "../../GameInstance.h"
#include "../CollisionHandler.h"
#include <math.h>

EnemyBase::EnemyBase(Point position, int flags) : ThingBase(flags | DRAW), maxVelocity(200) {
	this->position = position;
	this->timer.start();
	this->pathTimer.start();
}

EnemyBase::~EnemyBase() {}

void EnemyBase::draw() {
	if (this->texture.isLoaded()) this->texture.draw(this->position - this->parent->getRenderer());
}

// TODO: Make this generic <- what?
void EnemyBase::move(Point velocity) { 
	double tickRatio = this->movement.getValue();
	if (!tickRatio) return;
	Point px = velocity.getUnitVector() * tickRatio * this->maxVelocity;
	if (!px.isReal()) return;

	PositionLock lock(this->position);
	Point modified = px / 4.0;
	for (int i = 0; i < 4; i++) {
		this->position += modified;
		if (CollisionHandler::locationValid(this->shared_from_this())) {
			lock.update();
		} else break;
	}
	lock.revert();
	if (!this->turning) {
		this->angle = atan2(px.y, px.x);
	}
}

Point EnemyBase::pathFindTo(Point target) {
	return target * 2;
}

void EnemyBase::turn(double delta) {
	if (this->turning) {
		this->angle += delta;
	}
}

void EnemyBase::toggleTurn() {
	this->turning = !this->turning;
}
