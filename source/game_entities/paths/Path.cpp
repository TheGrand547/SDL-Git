#include "Path.h"

const int Path::REPEAT = 0;
const int Path::SINGLE_LOOP = -2;

Path::Path(EnemyBase* target) : ticksDone(0), target(target) {}

Path::~Path() {
	this->target = NULL;
}

void Path::setTarget(EnemyBase* target) {
	this->target = target;
}

bool Path::isStarted() const {
	return this->started;
}

void Path::update() {
	float tmp = this->timer.getTicks();
	if (tmp) {
		for (int i = 1; i < tmp; i++) {
			this->modify(1 / 10.0);
		}
		this->timer.start();
	}
}

void Path::pause() {
	this->timer.pause();
}

void Path::unpause() {
	this->timer.unpause();
}

bool Path::isPaused() {
	return this->timer.isPaused();
}
