#include "GameInstance.h"

typedef std::shared_ptr<ThingBase> ThingPtr;

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
							renderer(renderer), collision(this) {}

GameInstance::~GameInstance() {}

void GameInstance::addThing(const ThingPtr& thing) {
	if (valueInVector(this->allThings, thing)) {
		LOG("ERROR: Attempted to add duplicate object.");
		return;
	}
	this->allThings.push_back(thing);
	thing->setParent(this);
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

void GameInstance::update() {
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
	//this->nodes.drawGroup();
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

void GameInstance::addNode(Point position, std::string data) {
	// For some reason it can't be placed inline?
	if (!this->nodes.addNodeAt(position, data)) {
		LOG("Failure Placing Node at (%.1f, %.1f)", position.x, position.y);
	}
}

void GameInstance::instanceBegin() {
	// Do final things before playing starts
	for (const ThingPtr& p: this->allThings) {
		p->addNodes();
	}
	this->nodes.connectNodes();
	this->nodes.purge();
}
