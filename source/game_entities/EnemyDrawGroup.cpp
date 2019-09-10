#include "EnemyDrawGroup.h"
#include "BadTest.h"

EnemyDrawGroup::EnemyDrawGroup(CollideBaseGroup& collision, NodeDrawGroup& nav, SDL_Renderer* renderer, BoundedPoint& offset) {
	this->collide = &collision;
	this->nav = &nav;
	this->renderer = renderer;
	this->offset = &offset;
	this->powerslave = std::make_unique<AiBrain>();
	this->powerslave->addTempProng();
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

template<class Type, typename...Arguments>
void EnemyDrawGroup::create(Arguments... args) {
	Type* entity = new Type(this, args...);
	entity->setParent(this);
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
		this->powerslave->doBrainThings(entity);
		entity->update();
	}
}

void EnemyDrawGroup::drawGroup() {
	for (EnemyBase* entity: this->vector) {
		entity->draw(this->renderer, *this->offset);
	}
}

void EnemyDrawGroup::setDot(Dot* dot) {
	this->dot = dot;
}

Dot* EnemyDrawGroup::getDot() {
	return this->dot;
}

template void EnemyDrawGroup::create<BadTest, Point>(Point point); // :(
