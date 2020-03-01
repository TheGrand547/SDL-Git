#include "GameInstance.h"
typedef std::shared_ptr<ThingBase> ThingPtr;

bool compare::operator()(const ThingBase* lhs, const ThingBase* rhs) const {
	if (lhs->originDistance() < rhs->originDistance()) {
		return true;
	}
	if (lhs->originDistance() > rhs->originDistance()) {
		return false;
	}
	return lhs < rhs;
}

GameInstance::GameInstance(SDL_Renderer* renderer, BoundedPoint offset) : renderer(renderer), offset(offset), 
							collision(this), playableArea(0, 0, Screen::MAX_WIDTH, Screen::MAX_HEIGHT) {}

GameInstance::~GameInstance() {}

void GameInstance::addThing(ThingPtr thing) {
	this->allThings.push_back(thing);
	thing->setParent(this);
	if (thing->getFlags() & DRAW) {
		this->drawThings.push_back(thing);
		if (!this->drawOrder.insert(thing.get()).second) {
			// TOOD: Log duplicate instance
		}
	}
	if (thing->getFlags() & SOLID) {
		this->collisionThings.push_back(thing);
		if (!(thing->getFlags() & MOVEABLE)) {
			//std::cout << "This thing shouldn't move" << std::endl;
		}
	}
	if (thing->getFlags() & MOVEABLE) {
		this->movingThings.push_back(thing);
	}
}

void GameInstance::update() {
	for (ThingPtr& thing: this->movingThings) {
		Point position = thing->getPosition();
		thing->update();
		if (position != thing->getPosition()) {
			this->drawOrder.erase(thing.get());
			this->drawOrder.insert(thing.get());
		}
	}
}

void GameInstance::draw() {
	for (ThingBase* thing: this->drawOrder) {
		thing->draw(this->renderer, this->offset);
	} 
	this->nodes.drawGroup();
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
	this->nodes.addNodeAt(position, data);
}

void GameInstance::instanceBegin() {
	// Do final things before playing starts
	for (const ThingPtr& thing: this->allThings) {
		thing->addNodes();
	}
	this->nodes.connectNodes();
	//this->nodes.purge();
}
