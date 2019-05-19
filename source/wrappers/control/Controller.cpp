#include "Controller.h"
#include "ControllerCommand.h"
#include "BasicCommands.h"
#include<iostream>
#include<SDL2/SDL.h>

int myKeyCodeFromEvent(SDL_Event event) {
	return event.key.keysym.sym;
}


Controller::Controller(Configuration config, PointDelta* target) {
	this->config = config;
	this->target = target;
	
	this->keys[config["Right"]] = new ControllerCommand<PointDelta>(BASIC::PLAYER_RIGHT_KEYDOWN, BASIC::PLAYER_RIGHT_KEYUP, target);
	this->keys[config["Left"]] = new ControllerCommand<PointDelta>(BASIC::PLAYER_LEFT_KEYDOWN, BASIC::PLAYER_LEFT_KEYUP, target);
	this->keys[config["Up"]] = new ControllerCommand<PointDelta>(BASIC::PLAYER_UP_KEYDOWN, BASIC::PLAYER_UP_KEYUP, target);
	this->keys[config["Down"]] = new ControllerCommand<PointDelta>(BASIC::PLAYER_DOWN_KEYDOWN, BASIC::PLAYER_DOWN_KEYUP, target);
	/** TODO: Rewrite code based around some class that can handle more than just Point/PointDelta based methods **/
	/** TODO: Make this less awful **/
}


Controller::~Controller() {}

void Controller::handleEvents(SDL_Event e) {
	switch(e.type) {
		case SDL_KEYDOWN:
			if (e.key.repeat == 0) {
				if (this->keys[myKeyCodeFromEvent(e)] != NULL) {
					this->keys[myKeyCodeFromEvent(e)]->keyDownCommand();
				}
			}
			break;
		case SDL_KEYUP:
			if (e.key.repeat == 0) {
				if (this->keys[myKeyCodeFromEvent(e)] != NULL) {
					this->keys[myKeyCodeFromEvent(e)]->keyUpCommand();
				}
			}
			break;
	}
}
