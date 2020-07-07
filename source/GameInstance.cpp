#include "GameInstance.h"

// Comparator for the sake of the draw order pointer set
bool compare::operator()(const ThingBase* lhs, const ThingBase* rhs) const {
	if (lhs->originDistance() < rhs->originDistance()) {
		return true;
	}
	if (lhs->originDistance() > rhs->originDistance()) {
		return false;
	}
	return lhs < rhs;
}

GameInstance::GameInstance(SDL_Renderer* renderer, BoundedPoint offset) : offset(offset), playableArea(0, 0, Screen::MAX_WIDTH, Screen::MAX_HEIGHT), 
							renderer(renderer), collision(this), sectors(this) {}

GameInstance::~GameInstance() {}

void GameInstance::addThing(const ThingPtr& thing) {
	if (valueInVector(this->allThings, thing)) {
		LOG("ERROR: Attempted to add duplicate object.");
		return;
	}
	thing->setParent(this);
	this->allThings.push_back(thing);
	int flags = thing->getAbsoluteFlags();
	if (flags & DRAW) {
		this->drawThings.push_back(thing);
		this->drawOrder.insert(thing.get());
	}
	if (flags & SOLID) {
		this->collisionThings.push_back(thing);
	}
	if (flags & MOVEABLE) {
		this->movingThings.push_back(thing);
	}
}

void GameInstance::addPlayer(const std::shared_ptr<ThingBase>& thing) {
	this->PLAYER = thing;
	this->addThing(thing);
}

void GameInstance::update() {
	// TODO: Collision by objects in sectors, mid tier priority due to requiring sizeable reworking
	for (ThingPtr& thing: this->movingThings) {
		Point position = thing->getPosition();
		thing->update();
		// If the object has moved, its relative draw order might need to be adjusted
		if (position != thing->getPosition()) {
			this->drawOrder.erase(thing.get());
			this->drawOrder.insert(thing.get());
		}
	}
}

void GameInstance::draw() {
	for (ThingBase* thing: this->drawOrder) thing->draw(this->renderer, this->offset);
}

Rect GameInstance::getPlayableArea() const {
	return this->playableArea;
}

SDL_Renderer* GameInstance::getRenderer() {
	return this->renderer;
}

Point& GameInstance::getOffset() {
	return this->offset;
}

void GameInstance::instanceBegin() {
	// Do final things before playing starts
	this->sectors.connectSectors();
	this->sectors.purge();
}

ThingPtr GameInstance::getPlayer() {
	return this->PLAYER;
}
