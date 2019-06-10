#include "EnemyDrawGroup.h"

EnemyDrawGroup::EnemyDrawGroup() {}

EnemyDrawGroup::~EnemyDrawGroup() {
	for (std::vector<EnemyBase*>::iterator iter = this->vector.begin(); iter != this->vector.end(); iter++) {
		delete *iter;
	}
	
}

void EnemyDrawGroup::add(EnemyBase* entity) {
	this->vector.push_back(entity);
}

void EnemyDrawGroup::update() {
	for (EnemyBase* entity: this->vector) {
		entity->update();
	}
}

void EnemyDrawGroup::drawGroup() {
	for (EnemyBase* entity: this->vector) {
		entity->render();
	}
}
