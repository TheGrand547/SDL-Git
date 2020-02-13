#include "GameInstance.h"

bool compare::operator()(const ThingBase* lhs, const ThingBase* rhs) const {
	if (lhs->originDistance() < rhs->originDistance()) {
		return true;
	}
	if (lhs->originDistance() > rhs->originDistance()) {
		return false;
	}
	return lhs < rhs;
}

GameInstance::GameInstance(SDL_Renderer* renderer, BoundedPoint offset) : renderer(renderer), offset(offset), collision(this) {}

GameInstance::~GameInstance() {
	std::cout << "crash" << std::endl;
}

void GameInstance::addThing(std::shared_ptr<ThingBase> thing) {
	this->allThings.push_back(thing);
	thing->setParent(this);
	if (thing->getFlags() & DRAW) {
		this->drawThings.push_back(thing);
		//this->drawOrder.insert(thing.get());
		
		if(!this->drawOrder.insert(thing.get()).second){   
			std::cout << thing.get() << std::endl;
		}
	}
	if (thing->getFlags() & SOLID) {
		this->collisionThings.push_back(thing);
	}
	if (thing->getFlags() & MOVEABLE) {
		this->movingThings.push_back(thing);
	}
}

void GameInstance::update() {
	for (std::shared_ptr<ThingBase> thing: this->movingThings) {
		Point position = thing->getPosition();
		///thing->move();
		/*
		if (position != thing->getPosition()) {
			this->drawOrder.erase(thing.get());
			this->drawOrder.insert(thing.get());
		}*/
	}
}

void GameInstance::draw() {
	for (ThingBase* thing: this->drawOrder) {
		thing->draw(this->renderer, this->offset);
	} 
}

SDL_Renderer* GameInstance::getRenderer() {
	return this->renderer;
}

Point& GameInstance::getOffset() {
	return this->offset;
}

void GameInstance::addNode(Point position, std::string data, bool full) {
	if (full) {
		this->nodes.addNodeAt(position, data);
	} else {
		this->nodes.addNullNodeAt(position, data);
	}
}

void GameInstance::instanceBegin() {
	// Do final things before playing starts
	this->nodes.purge();
}
