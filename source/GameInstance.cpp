#include "GameInstance.h"

// Comparator for the sake of the draw order pointer set
bool Draw::compare::operator()(const ThingBase* lhs, const ThingBase* rhs) const {
	if (lhs->originDistance() < rhs->originDistance()) {
		return true;
	}
	if (lhs->originDistance() > rhs->originDistance()) {
		return false;
	}
	return lhs < rhs;
}

GameInstance::GameInstance(SDL_Window* window, SDL_Renderer* renderer, BoundedPoint offset) : started(false), renderer({offset, renderer}), 
							playableArea(0, 0, Screen::MAX_WIDTH, Screen::MAX_HEIGHT), window(window), ground(this), 
							collision(this), sectors(this) {
	this->frameTimer.start();
}

GameInstance::~GameInstance() {}

void GameInstance::addThing(const ThingPtr& thing) {
	TRACE("Adding thing at %ld", (long int) thing.get());
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
	} else {
		this->updateThings.push_back(thing);
	}
}

void GameInstance::removeThing(const ThingPtr& thing) {
	removeValue(this->allThings, thing);
	int flags = thing->getAbsoluteFlags();
	if (flags & SOLID) removeValue(this->collisionThings, thing);
	if (flags & DRAW) {
		removeValue(this->drawThings, thing);
		removeValue(this->drawOrder, thing.get());
	}
	if (flags & MOVEABLE) {
		removeValue(this->movingThings, thing);
	} else {
		removeValue(this->updateThings, thing);
	}
	
}

void GameInstance::addPlayer(const std::shared_ptr<ThingBase>& thing) {
	this->PLAYER = thing;
	this->addThing(thing);
}

void GameInstance::draw() {
	// Update screen position before drawing is done
	if (this->getPlayer()->getPosition().x < Screen::SCREEN_WIDTH / 2) this->renderer.offset.x = 0;
	if (this->getPlayer()->getPosition().y < Screen::SCREEN_HEIGHT / 2) this->renderer.offset.y = 0;
	if (this->getPlayer()->getPosition().x > Screen::MAX_X_SCROLL_DISTANCE) this->renderer.offset.x = Screen::MAX_SCREEN_X_POS;
	if (this->getPlayer()->getPosition().y > Screen::MAX_Y_SCROLL_DISTANCE) this->renderer.offset.y = Screen::MAX_SCREEN_Y_POS;
	
	// Draw things
	this->ground.drawGroup();
	for (ThingBase* thing: this->drawOrder) thing->draw();
}

void GameInstance::finalizeFrame() {
	// Render changes to the window
	SDL_RenderPresent(this->renderer.renderer);
	SDL_UpdateWindowSurface(this->window);
	
	// Clear the window for the next frame to draw onto
	SDL_SetRenderDrawColor(this->renderer.renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(this->renderer.renderer);
	
	// If framerate is soft capped, delay if the framerate is over 1000
	if (!this->gameState["cv_capped_fps"] && !this->frameTimer.getTicks()) SDL_Delay(1);
	
	// Reset timer
	this->frameTimer.start();
}

void GameInstance::instanceBegin() { // Do final things before playing starts
	TRACE("Instance Begin");
	
	if (this->started) return; // Don't needlessly bog down the system
	// Do cleanup on the pathfinding system
	this->sectors.connectSectors();
	this->sectors.purge();
	this->collision.finalize();
	
	// Clean up the rendering for the background group
	this->ground.finalize();
	
	this->started = true;
}


void GameInstance::update() {
	TRACE("Update Begin");
	if (!this->started) this->instanceBegin();
	// TODO: Collision by objects in sectors, mid tier priority due to requiring sizeable reworking
	for (ThingPtr& thing: this->movingThings) {
		if (!thing) break;
		Point position = thing->getPosition();
		thing->update();
		// If the object has moved, its relative draw order might need to be adjusted
		if (position != thing->getPosition()) {
			std::set<ThingBase*, Draw::compare>::iterator iterator = this->drawOrder.find(thing.get());
			if (iterator != this->drawOrder.end()) {
				this->drawOrder.erase(iterator);
				this->drawOrder.insert(thing.get());
			}
		}
	}
	TRACE("Update Mid");
	for (ThingPtr& thing: this->updateThings) thing->update();
	TRACE("Update End");
}

Rect GameInstance::getPlayableArea() const {
	return this->playableArea;
}

Renderer& GameInstance::getRenderer() {
	return this->renderer;
}

SDL_Renderer* GameInstance::getTrueRenderer() {
	return this->renderer.renderer;
}

Point& GameInstance::getOffset() {
	return this->renderer.offset;
}

ThingPtr GameInstance::getPlayer() {
	return this->PLAYER;
}
