#include "GameInstance.h"

bool compare::operator()(const ThingBase* lhs, const ThingBase* rhs) {
	return lhs->originDistance() < rhs->originDistance();
}

GameInstance::GameInstance() {}

GameInstance::~GameInstance() {}

void GameInstance::addThing(std::shared_ptr<ThingBase> thing) {
	this->allThings.push_back(thing);
	if (thing->getFlags() & DRAW) {
		this->drawThings.push_back(thing);
	}
	if (thing->getFlags() & SOLID) {
		this->collision.push_back(thing);
	}
	if (thing->getFlags() & MOVEABLE) {
		this->movingThings.push_back(thing);
	}
	this->drawOrder.insert(thing.get());
}

void GameInstance::update() {
	for (std::shared_ptr<ThingBase> thing: this->movingThings) {
		///thing->move();
		if (!(thing->getFlags() & NOCLIP)) {
			
		}
		this->drawOrder.erase(thing.get());
		this->drawOrder.insert(thing.get());
	}
}
