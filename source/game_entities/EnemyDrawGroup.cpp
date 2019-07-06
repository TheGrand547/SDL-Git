#include "EnemyDrawGroup.h"

EnemyDrawGroup::EnemyDrawGroup() {}

EnemyDrawGroup::~EnemyDrawGroup() {
	for (std::vector<EnemyBase*>::iterator iter = this->vector.begin(); iter != this->vector.end(); iter++) {
		delete *iter;
	}
	this->dot = NULL;
}

void EnemyDrawGroup::add(EnemyBase* entity) {
	entity->setCollision(this->collide);
	entity->setNavigation(this->nav);
	this->vector.push_back(entity);
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
