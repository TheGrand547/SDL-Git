#include "Controller.h"
#include "ControllerCommand.h"
#include "BasicCommands.h"
#include<iostream>
#include<SDL2/SDL.h>
#include "../../essential/util.h"

int scanCodeFromEvent(SDL_Event event) {
	return event.key.keysym.scancode;
}


Controller::Controller(Configuration config) {
	this->config = config;
}


Controller::~Controller() {
	for(std::map<int, CommandBase*>::iterator iterator = keys.begin(); iterator != keys.end(); iterator++) {
		delete iterator->second;
	}
}

void Controller::handleEvents() {
	SDL_Event e;
	SDL_PumpEvents();
	while(SDL_PollEvent(&e) != 0) {
		switch(e.type) {
			case SDL_QUIT:
				this->quit = true;
				break;
			case SDL_KEYDOWN:
				if (e.key.repeat == 0) {
					/*
					if (this->keys[scanCodeFromEvent(e)] != NULL) {
						this->keys[scanCodeFromEvent(e)]->keyDownCommand();
					}*/
					if (this->listeners[scanCodeFromEvent(e)].maxHeld > 0) {
						this->listeners[scanCodeFromEvent(e)].set(true);
					}
				}
				break;
			case SDL_KEYUP:
				if (e.key.repeat == 0) {
					/*
					if (this->keys[scanCodeFromEvent(e)] != NULL) {
						this->keys[scanCodeFromEvent(e)]->keyUpCommand();
					}*/
					if (this->listeners[scanCodeFromEvent(e)].maxHeld > 0) {
						this->listeners[scanCodeFromEvent(e)].set(false);
					}
				}
				break;
		}
	}
	for(std::map<int, CommandBase*>::iterator iterator = keys.begin(); iterator != keys.end(); iterator++) {
		iterator->second->keyUpCommand();
	}
	for(std::map<int, CommandBase*>::iterator iterator = keys.begin(); iterator != keys.end(); iterator++) {
		if (this->stuff[iterator->first]) {
			if (iterator->second != NULL) {
				iterator->second->keyDownCommand();
			}
		}
	}
	this->tickListeners();	
}

void Controller::addKey(int value, CommandBase* command) {
	this->keys[value] = command;
}

void Controller::addListener(int key, int threshold) {
	this->listeners[key] = HeldKey(threshold);
}

void Controller::addListener(std::string key, int threshold) {
	this->addListener(config[key], threshold);
}

void Controller::tickListeners() {
	for(std::map<int, HeldKey>::iterator iterator = this->listeners.begin(); iterator != listeners.end(); iterator++) {
		iterator->second.tick();
	}
}

HeldKey& Controller::checkListener(int key) {
	return this->listeners[key];
}

void Controller::addPlayerKeys(PointDelta* target) {
	this->addKey(config["Right"], new ControllerCommand<PointDelta>(BASIC::PLAYER_RIGHT_KEYDOWN, BASIC::PLAYER_RIGHT_KEYUP, target));
	this->addKey(config["Left"], new ControllerCommand<PointDelta>(BASIC::PLAYER_LEFT_KEYDOWN, BASIC::PLAYER_LEFT_KEYUP, target));
	this->addKey(config["Up"], new ControllerCommand<PointDelta>(BASIC::PLAYER_UP_KEYDOWN, BASIC::PLAYER_UP_KEYUP, target));
	this->addKey(config["Down"], new ControllerCommand<PointDelta>(BASIC::PLAYER_DOWN_KEYDOWN, BASIC::PLAYER_DOWN_KEYUP, target));
}
