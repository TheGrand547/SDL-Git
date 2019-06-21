#include "Controller.h"
#include "ControllerCommand.h"
#include "BasicCommands.h"
#include "PlayerMoveCommand.h"
#include<iostream>
#include<SDL2/SDL.h>
#include<string>
#include<sstream>
#include "../../essential/util.h"  

int scanCodeFromEvent(SDL_Event event) {
	return event.key.keysym.scancode;
}


Controller::Controller() {
}


Controller::~Controller() {
	for (std::map<int, CommandBase*>::iterator iterator = keys.begin(); iterator != keys.end(); iterator++) {
		delete iterator->second;
	}
	for (std::map<int, ButtonCommand*>::iterator iterator = buttons.begin(); iterator != buttons.end(); iterator++) {
		delete iterator->second;
	}
}

void Controller::handleEvents() {
	SDL_Event e;
	SDL_PumpEvents();
	SDL_GetMouseState(&mouseX, &mouseY);
	while(SDL_PollEvent(&e) != 0) {
		switch(e.type) {
			case SDL_QUIT:
				this->quit = true;
				break;
			case SDL_KEYDOWN:
				if (e.key.repeat == 0) {
					this->myq.push_back(*SDL_GetKeyName(e.key.keysym.sym));
					if (this->keys[scanCodeFromEvent(e)] != NULL) {
						this->keys[scanCodeFromEvent(e)]->keyDownCommand();
					}
					if (this->listeners[scanCodeFromEvent(e)].maxHeld > 0) {
						this->listeners[scanCodeFromEvent(e)].set(true);
					}
				}
				break;
			case SDL_KEYUP:
				if (e.key.repeat == 0) {
					if (this->keys[scanCodeFromEvent(e)] != NULL) {
						this->keys[scanCodeFromEvent(e)]->keyUpCommand();
					}
					if (this->listeners[scanCodeFromEvent(e)].maxHeld > 0) {
						this->listeners[scanCodeFromEvent(e)].set(false);
					}
				}
				break;
		}
	}
	
	if (this->myq.size() >= 1) {
		std::stringstream tmp;
		tmp.str("");
		for (int i = 0; i < this->myq.size(); i++) {
			tmp << char(tolower(this->myq[i]));
			for (std::map<std::string, void(*)()>::iterator iterator = this->mymp.begin(); iterator != this->mymp.end(); iterator++) {
				if (iterator->first == tmp.str()) {
					if (iterator->second != NULL) {
						iterator->second();
						this->myq.clear();
						break;
					}
				}
			}
		}
	}
	for (std::map<int, ButtonCommand*>::iterator iterator = buttons.begin(); iterator != buttons.end(); iterator++) {
		if (this->stuff[iterator->first]) {
			if (iterator->second != NULL) {
				iterator->second->execute();
			}
		}
	}
	this->tickListeners();	
}

void Controller::addButton(int value, ButtonCommand* button) {
	this->buttons[value] = button;
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
	this->addButton(config["Right"], new PlayerMoveCommand(BASIC::PLAYER_RIGHT_KEYDOWN, target));
	this->addButton(config["Left"], new PlayerMoveCommand(BASIC::PLAYER_LEFT_KEYDOWN, target));
	this->addButton(config["Up"], new PlayerMoveCommand(BASIC::PLAYER_UP_KEYDOWN, target));
	this->addButton(config["Down"], new PlayerMoveCommand(BASIC::PLAYER_DOWN_KEYDOWN, target));
}

void Controller::addCheat(std::string key, void(*func)()) {
	this->mymp[key] = func;
}
