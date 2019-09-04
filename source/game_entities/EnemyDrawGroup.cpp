#include "EnemyDrawGroup.h"

EnemyDrawGroup::EnemyDrawGroup() {}

EnemyDrawGroup::~EnemyDrawGroup() {
	this->clearGroup();
	this->dot = NULL;
}

bool EnemyDrawGroup::exists() {
	return this->vector.size() > 0;
}


int EnemyDrawGroup::size() {
	return this->vector.size();
}

void EnemyDrawGroup::add(EnemyBase* entity) {
	entity->setCollision(this->collide);
	entity->setNavigation(this->nav);
	if (entity->isLocationInvalid()) {
		delete entity;
		return;
	}
	this->vector.push_back(entity);
}

void EnemyDrawGroup::clearGroup() {
	std::vector<EnemyBase*>::iterator iter = this->vector.begin();
	for (; iter != this->vector.end(); iter++) {
		delete iter[0];
	}
	this->vector.clear();
}

void EnemyDrawGroup::update() {
	for (EnemyBase* entity: this->vector) {
		entity->update();
	}
}

void EnemyDrawGroup::drawGroup() {
	for (EnemyBase* entity: this->vector) {
		entity->draw(this->dot);
	}
}

void EnemyDrawGroup::setDot(Dot* dot) {
	this->dot = dot;
}

void EnemyDrawGroup::setCollision(CollideBaseGroup& collision) {
	this->collide = &collision;
}

void EnemyDrawGroup::setNavigation(NodeDrawGroup& nav) {
	this->nav = &nav;
}
