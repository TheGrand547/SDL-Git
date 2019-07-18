#include "EnemyDrawGroup.h"

EnemyDrawGroup::EnemyDrawGroup() {}

EnemyDrawGroup::~EnemyDrawGroup() {
	this->clearGroup();
	this->dot = NULL;
}

int EnemyDrawGroup::size() {
	return this->vector.size();
}

void EnemyDrawGroup::add(EnemyBase* entity) {
	entity->setCollision(this->collide);
	entity->setNavigation(this->nav);
	if (entity->checkLocationValidity()) {
		delete entity;
		return;
	}
	this->vector.push_back(entity);
}

void EnemyDrawGroup::clearGroup() {
	for (std::vector<EnemyBase*>::iterator iter = this->vector.begin(); iter != this->vector.end(); iter++) {
		delete *iter;
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
		entity->render(this->dot);
	}
}

void EnemyDrawGroup::setDot(Dot* dot) {
	this->dot = dot;
}

void EnemyDrawGroup::setCollision(CollideBaseGroup* collision) {
	this->collide = collision;
}

void EnemyDrawGroup::setNavigation(NodeDrawGroup* nav) {
	this->nav = nav;
}
