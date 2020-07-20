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

GameInstance::GameInstance(SDL_Window* window, SDL_Renderer* renderer, BoundedPoint offset) : offset(offset), playableArea(0, 0, Screen::MAX_WIDTH, Screen::MAX_HEIGHT), 
							renderer(renderer), window(window), ground(this), collision(this), sectors(this) {}

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
	if (flags & HAS_EFFECT_ZONES) {
		this->zoneThings.push_back(thing);
	}
}

void GameInstance::addPlayer(const std::shared_ptr<ThingBase>& thing) {
	this->PLAYER = thing;
	this->addThing(thing);
}

void GameInstance::draw() {
	// Update screen position before drawing is done
	if (this->getPlayer()->getPosition().x < Screen::SCREEN_WIDTH / 2) this->offset.x = 0;
	if (this->getPlayer()->getPosition().y < Screen::SCREEN_HEIGHT / 2) this->offset.y = 0;
	if (this->getPlayer()->getPosition().x > Screen::MAX_X_SCROLL_DISTANCE) this->offset.x = Screen::MAX_SCREEN_X_POS;
	if (this->getPlayer()->getPosition().y > Screen::MAX_Y_SCROLL_DISTANCE) this->offset.y = Screen::MAX_SCREEN_Y_POS;
	
	// Draw things
	this->ground.drawGroup();
	for (ThingBase* thing: this->drawOrder) thing->draw(this->renderer, this->offset);
}

void GameInstance::finalizeFrame() {
	// Render changes to the window
	SDL_RenderPresent(this->renderer);
	SDL_UpdateWindowSurface(this->window);
	
	// Clear the window for the next frame to draw onto
	/*
	SDL_SetRenderDrawColor(this->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(this->renderer);*/
}

void GameInstance::instanceBegin() {
	// Do final things before playing starts
	this->sectors.connectSectors();
	this->sectors.purge();
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

Rect GameInstance::getPlayableArea() const {
	return this->playableArea;
}

SDL_Renderer* GameInstance::getRenderer() {
	return this->renderer;
}

Point& GameInstance::getOffset() {
	return this->offset;
}

ThingPtr GameInstance::getPlayer() {
	return this->PLAYER;
}
