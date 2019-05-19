#include "Controller.h"
#include "ControllerCommand.h"
#include<iostream>
#include<SDL2/SDL.h>

int myKeyCodeFromEvent(SDL_Event event) {
	return event.key.keysym.sym;
}


Controller::Controller(Configuration config, PointDelta* target) {
	this->config = config;
	this->target = target;
	
	/** TODO: Rewrite code based around some class that can handle more than just Point/PointDelta based methods **/
	/** TODO: Make this less awful **/
	this->addKey("Right", Controller::ADD, this->target->getXPoint(), Controller::GREATER_ZERO, Controller::X_ZERO);
	this->addKey("Left", Controller::SUBTRACT, this->target->getXPoint(), Controller::LESSER_ZERO, Controller::X_ZERO);
	this->addKey("Down", Controller::ADD, this->target->getYPoint(), Controller::GREATER_ZERO, Controller::Y_ZERO);
	this->addKey("Up", Controller::SUBTRACT, this->target->getYPoint(), Controller::LESSER_ZERO, Controller::Y_ZERO);
}

Controller::~Controller() {}

void Controller::handleEvents(SDL_Event e) {
	switch(e.type) {
		case SDL_KEYDOWN:
			if (e.key.repeat == 0) {
				if (this->keydown[myKeyCodeFromEvent(e)] != NULL) 
					this->keydown[myKeyCodeFromEvent(e)]->execute();	
			}
			break;
		case SDL_KEYUP:
			if (e.key.repeat == 0) {
				if (this->keyup[myKeyCodeFromEvent(e)] != NULL) 
					this->keyup[myKeyCodeFromEvent(e)]->execute();
			}
			break;
	}
}

void Controller::addKey(int key, void(*keyDownCommand)(PointDelta*, Point), Point keyDownArgument, void(*keyUpCommand)(PointDelta*, void(*)(PointDelta*)), void(*keyUpArgument)(PointDelta*)) {
	this->keydown[key] = new ControllerCommand<PointDelta, Point>(keyDownCommand, this->target, keyDownArgument);
	this->keyup[key] = new ControllerCommand<PointDelta, void(*)(PointDelta*)>(keyUpCommand, this->target, keyUpArgument);
}

void Controller::addKey(std::string key, void(*keyDownCommand)(PointDelta*, Point), Point keyDownArgument, void(*keyUpCommand)(PointDelta*, void(*)(PointDelta*)), void(*keyUpArgument)(PointDelta*)) {
	if (this->config[key] != 0) {
		this->addKey(this->config[key], keyDownCommand, keyDownArgument, keyUpCommand, keyUpArgument);
		return;
	}
	this->addKey(SDL_GetKeyFromName(key.c_str()), keyDownCommand, keyDownArgument, keyUpCommand, keyUpArgument);
}
