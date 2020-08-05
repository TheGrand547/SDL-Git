#include "Path.h"

const int Path::REPEAT = 0;
const int Path::SINGLE_LOOP = -2;

Path::Path(EnemyBase* target) : ticksDone(0), target(target) {}

Path::~Path() {
	this->target = NULL;
}

bool Path::isPaused() const {
	return this->timer.isPaused();
}

bool Path::isStarted() const {
	return this->started;
}

void Path::pause() {
	this->timer.pause();
}

void Path::setTarget(EnemyBase* target) {
	this->target = target;
}

void Path::unpause() {
	this->timer.unpause();
}

void Path::update() {
	if (double tmp = this->timer.getTicks()) {
		for (int i = 1; i < tmp; i++) this->modify(1 / 10.0);
		this->timer.start();
	}
}
