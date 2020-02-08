#include "GameInstance.h"

bool compare::operator()(const ThingBase* lhs, const ThingBase* rhs) {
	return lhs->originDistance() < rhs->originDistance();
}

GameInstance::GameInstance(SDL_Renderer* renderer, BoundedPoint offset) : renderer(renderer), offset(offset) {}

GameInstance::~GameInstance() {}

void GameInstance::addThing(std::shared_ptr<ThingBase> thing) {
	this->allThings.push_back(thing);
	thing->setParent(this);
	if (thing->getFlags() & DRAW) {
		this->drawThings.push_back(thing);
	}
	if (thing->getFlags() & SOLID) {
		this->collisionThings.push_back(thing);
	}
	if (thing->getFlags() & MOVEABLE) {
		this->movingThings.push_back(thing);
	}
	this->drawOrder.insert(thing.get());
}

void GameInstance::update() {
	for (std::shared_ptr<ThingBase> thing: this->movingThings) {
		Point position = thing->getPosition();
		///thing->move();
		if (position != this->getPosition()) {
			this->drawOrder.erase(thing.get());
			this->drawOrder.insert(thing.get());
		}
	}
}

void GameInstance::draw() {
	for (std::shared_ptr<ThingBase> thing: this->drawOrder) {
		thing->draw();
	} 
}

SDL_Renderer* GameInstance::getRenderer() {
	return this->renderer;
}

BoundedPoint& GameInstance::getOffset() {
	return this->offset;
}

void GameInstance::addNode(Point position, std::string data, bool full) {
	if (full) {
		this->nodes.addNodeAt(position, data);
	} else {
		this->nodes.addNullNodeAt(point, data);
	}
}

void GameInstance::instanceBegin() {
	// Do final things before playing starts
	this->nodes.purge();
}
