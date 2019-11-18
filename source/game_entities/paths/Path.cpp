#include "Path.h"
#include<iostream> // die

Path::Path(EnemyBase* target) {
	this->ticksDone = 0;
	this->target = target;
}

Path::~Path() {
	this->target = NULL;
}

void Path::stop() {
	this->timer.stop();
	this->ticksDone = 0;
}

void Path::start() {
	this->timer.start();
}

void Path::setTarget(EnemyBase* target) {
	this->target = target;
}

void Path::update() {
	float tmp = this->timer.getTicks();
	for (int i = 1; i < tmp; i++) {
		this->modify(1 / 10.0);
	}
	this->timer.start();
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
