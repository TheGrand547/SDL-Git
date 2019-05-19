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
	
	this->keys[config["Right"]] = ControllerCommand<PointDelta>(BASIC::PLAYER_RIGHT_KEYDOWN, BASIC::PLAYER_RIGHT_KEYUP, target);
	this->keys[config["Left"]] = ControllerCommand<PointDelta>(BASIC::PLAYER_LEFT_KEYDOWN, BASIC::PLAYER_LEFT_KEYUP, target);
	this->keys[config["Up"]] = ControllerCommand<PointDelta>(BASIC::PLAYER_UP_KEYDOWN, BASIC::PLAYER_UP_KEYUP, target);
	this->keys[config["Down"]] = ControllerCommand<PointDelta>(BASIC::PLAYER_DOWN_KEYDOWN, BASIC::PLAYER_DOWN_KEYUP, target);
	/** TODO: Rewrite code based around some class that can handle more than just Point/PointDelta based methods **/
	/** TODO: Make this less awful **/
	/*
	this->addKey("Right", Controller::ADD, this->target->getXPoint(), Controller::GREATER_ZERO, Controller::X_ZERO);
	this->addKey("Left", Controller::SUBTRACT, this->target->getXPoint(), Controller::LESSER_ZERO, Controller::X_ZERO);
	this->addKey("Down", Controller::ADD, this->target->getYPoint(), Controller::GREATER_ZERO, Controller::Y_ZERO);
	this->addKey("Up", Controller::SUBTRACT, this->target->getYPoint(), Controller::LESSER_ZERO, Controller::Y_ZERO);
	*/
	
	for (std::map<int, CommandBase>::iterator iter = this->keys.begin(); iter != this->keys.end(); iter++) {
		std::cout << iter->first << " = " <<std::endl;
	}
	
}


Controller::~Controller() {}

void Controller::handleEvents(SDL_Event e) {
	switch(e.type) {
		case SDL_KEYDOWN:
			std::cout << myKeyCodeFromEvent(e) << std::endl;
			if (e.key.repeat == 0) {
				this->keys[myKeyCodeFromEvent(e)].keyDownCommand();
			}
			break;
		case SDL_KEYUP:
			if (e.key.repeat == 0) {
				this->keys[myKeyCodeFromEvent(e)].keyUpCommand();
			}
			break;
	}
}

void Controller::addKey(int key, void(*keyDownCommand)(PointDelta*, Point), Point keyDownArgument, void(*keyUpCommand)(PointDelta*, void(*)(PointDelta*)), void(*keyUpArgument)(PointDelta*)) {
	//this->keydown[key] = new ControllerCommand<PointDelta, Point>(keyDownCommand, this->target, keyDownArgument);
	//this->keyup[key] = new ControllerCommand<PointDelta, void(*)(PointDelta*)>(keyUpCommand, this->target, keyUpArgument);
}

void Controller::addKey(std::string key, void(*keyDownCommand)(PointDelta*, Point), Point keyDownArgument, void(*keyUpCommand)(PointDelta*, void(*)(PointDelta*)), void(*keyUpArgument)(PointDelta*)) {
	/*
	if (this->config[key] != 0) {
		this->addKey(this->config[key], keyDownCommand, keyDownArgument, keyUpCommand, keyUpArgument);
		return;
	}
	this->addKey(SDL_GetKeyFromName(key.c_str()), keyDownCommand, keyDownArgument, keyUpCommand, keyUpArgument);
	*/
}

