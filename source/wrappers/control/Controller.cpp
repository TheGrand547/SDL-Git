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

Controller::Controller() {}


Controller::~Controller() {
	this->keys.clear();
	this->buttons.clear();
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
					if (scanCodeFromEvent(e) == this->config["Exit"]) { // Band-aid fix
						this->quit = true;
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
	if (this->myq.size() > 0) {
		std::stringstream tmp;
		tmp.str("");
		for (int i = 0; i < this->myq.size(); i++) {
			tmp << char(tolower(this->myq[i]));
			std::map<std::string, void(*)()>::iterator iterator = this->mymp.begin();
			for (; iterator != this->mymp.end(); iterator++) {
				if (tmp.str().find(iterator->first) != std::string::npos) {
					if (iterator->second != NULL) {
						iterator->second();
						this->myq.clear();
						break;
					}
				}
			}
		}
	}
	std::map<int, std::shared_ptr<ButtonCommand>>::iterator iterator = buttons.begin();
	for (; iterator != buttons.end(); iterator++) {
		if (this->stuff[iterator->first]) {
			if (iterator->second != NULL) {
				iterator->second->execute();
			}
		}
	}
	this->updateListeners();	
}

void Controller::addButton(int value, std::shared_ptr<ButtonCommand> button) {
	this->buttons[value] = button;
}

void Controller::addButton(std::string str, std::shared_ptr<ButtonCommand> button) {
	this->buttons[config[str]] = button;
}

void Controller::addKey(int value, std::shared_ptr<CommandBase> command) {
	this->keys[value] = command;
}

void Controller::addListener(int key, int threshold) {
	this->listeners[key] = HeldKey(threshold);
}

void Controller::addListener(std::string key, int threshold) {
	this->addListener(config[key], threshold);
}

void Controller::updateListeners() {
	for(std::map<int, HeldKey>::iterator iterator = this->listeners.begin(); iterator != listeners.end(); iterator++) {
		iterator->second.set(this->stuff[iterator->first]);
	}
}

HeldKey& Controller::checkListener(int key) {
	return this->listeners[key];
}

void Controller::addPlayerKeys(PointDelta& target) {
	this->addButton(config["Right"], std::make_shared<PlayerMoveCommand>(BASIC::PLAYER_RIGHT_KEYDOWN, &target));
	this->addButton(config["Left"], std::make_shared<PlayerMoveCommand>(BASIC::PLAYER_LEFT_KEYDOWN, &target));
	this->addButton(config["Up"], std::make_shared<PlayerMoveCommand>(BASIC::PLAYER_UP_KEYDOWN, &target));
	this->addButton(config["Down"], std::make_shared<PlayerMoveCommand>(BASIC::PLAYER_DOWN_KEYDOWN, &target));
}

void Controller::addCheat(std::string key, void(*func)()) {
	this->mymp[key] = func;
}
