#include "GameInstance.h"
#include "game_entities/base/ThingBase.h"
#include "game_entities/CollisionHandler.h"

GameInstance::GameInstance(SDL_Window* window, SDL_Renderer* renderer, BoundedPoint offset) : iterating(false), started(false), 
							renderer({offset, renderer}), playableArea(0, 0, Screen::maxWidth, Screen::maxHeight), window(window),
							ground(this), sectors(this) {
	this->frameTimer.start();
	this->text.parent = this;
	CollisionHandler::setTarget(this);
}

GameInstance::~GameInstance() {}

void GameInstance::addThing(const ThingPtr& thing) {
	if (this->iterating) {
		this->delayed.push(thing);
		return;
	}
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
	}
	if (flags & SOLID) {
		this->collisionThings.push_back(thing);
	}
	if (flags & MOVEABLE) {
		this->movingThings.push_back(thing);
	} else {
		this->updateThings.push_back(thing);
	}
	TRACE("Finished adding thing");
}

void GameInstance::removeThing(const ThingPtr& thing) {
	removeValue(this->allThings, thing);
	int flags = thing->getAbsoluteFlags();
	if (flags & SOLID) removeValue(this->collisionThings, thing);
	if (flags & DRAW) {
		removeValue(this->drawThings, thing);
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
	// The .05 thing is to stop off by one errors. Yes I know this sounds idiotic but it works, somehow
	if (this->getPlayer()->getPosition().x < Screen::width / 2) this->renderer.offset.x = .05;
	if (this->getPlayer()->getPosition().y < Screen::height / 2) this->renderer.offset.y = .05;
	if (this->getPlayer()->getPosition().x > Screen::xScrollMax) this->renderer.offset.x = Screen::xPositionMax;
	if (this->getPlayer()->getPosition().y > Screen::yScrollMax) this->renderer.offset.y = Screen::yPositionMax;

	// Draw things
	this->ground.drawGroup();
	for (ThingPtr& thing: this->drawThings) thing->draw();
	this->PLAYER->draw();
	this->text.draw();
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
	
	// Removed due to empty function, might return later
	//this->collision.finalize();

	// Clean up the rendering for the background group
	this->ground.finalize();

	this->started = true;
}

void GameInstance::queueRemoval(const ThingPtr& thing) {
	this->remove.push(thing);
}

void GameInstance::update() {
	this->iterating = true;
	TRACE("Update Begin");
	if (!this->started) this->instanceBegin();
	TRACE("Update Statics");
	for (ThingPtr& thing: this->updateThings) thing->update();
	TRACE("Update Moving");
	for (ThingPtr& thing: this->movingThings) {
		Point position = thing->getPosition();
		thing->update();
	}
	TRACE("Update Removal");
	while (this->remove.size()) {
		this->removeThing(this->remove.front());
		this->remove.pop();
	}
	this->iterating = false;
	TRACE("Update Add Delayed Objects");
	while (this->delayed.size()) {
		this->addThing(this->delayed.front());
		this->delayed.pop();
	}
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
