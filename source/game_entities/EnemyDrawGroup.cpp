#include "EnemyDrawGroup.h"
#include "BadTest.h"

EnemyDrawGroup::EnemyDrawGroup(CollideBaseGroup& collision, NodeDrawGroup& nav, SDL_Renderer* renderer, BoundedPoint& offset) {
	this->collide = &collision;
	this->nav = &nav;
	this->renderer = renderer;
	this->offset = &offset;
}

EnemyDrawGroup::~EnemyDrawGroup() {
	this->clearGroup();
}

bool EnemyDrawGroup::exists() {
	return this->vector.size() > 0;
}

int EnemyDrawGroup::size() {
	return this->vector.size();
}

void EnemyDrawGroup::add(std::shared_ptr<EnemyBase> entity) {
	//entity->setParent(this);
	if (entity->isLocationInvalid()) {
		entity.reset();
		return;
	}
	this->vector.push_back(entity);
}

void EnemyDrawGroup::clearGroup() {
	this->vector.clear();
}

void EnemyDrawGroup::update() {
	for (std::shared_ptr<EnemyBase> entity: this->vector) {
		entity->update();
	}
}

void EnemyDrawGroup::drawGroup() {
	for (std::shared_ptr<EnemyBase> entity: this->vector) {
		entity->draw(this->renderer, *this->offset);
	}
}


void EnemyDrawGroup::setDot(Dot* dot) {
	this->dot = dot;
}

Dot* EnemyDrawGroup::getDot() {
	return this->dot;
}
