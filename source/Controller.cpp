#include "Controller.h"
#include "essential/util.h"

Controller::Controller(Configuration config, PointDelta* target) {
	this->config = config;
	this->target = target;		
	
	this->keydown[config["Right"]] = new ControllerCommand<PointDelta, Point>(Controller::ADD, this->target, this->target->getXPoint());
	this->keydown[config["Left"]] = new ControllerCommand<PointDelta, Point>(Controller::SUBTRACT, this->target, this->target->getXPoint());
	this->keydown[config["Up"]] = new ControllerCommand<PointDelta, Point>(Controller::SUBTRACT, this->target, this->target->getYPoint());
	this->keydown[config["Down"]] = new ControllerCommand<PointDelta, Point>(Controller::ADD, this->target, this->target->getYPoint());
	
	
	this->keyup[config["Right"]] = new ControllerCommand<PointDelta, void(*)(PointDelta*)>(Controller::GREATER_ZERO, this->target, Controller::X_ZERO);
	this->keyup[config["Left"]] = new ControllerCommand<PointDelta, void(*)(PointDelta*)>(Controller::LESSER_ZERO, this->target, Controller::X_ZERO);
	this->keyup[config["Up"]] = new ControllerCommand<PointDelta, void(*)(PointDelta*)>(Controller::LESSER_ZERO, this->target, Controller::Y_ZERO);
	this->keyup[config["Down"]] = new ControllerCommand<PointDelta, void(*)(PointDelta*)>(Controller::GREATER_ZERO, this->target, Controller::Y_ZERO);
}

Controller::~Controller() {}

void Controller::handleEvents(SDL_Event e) {
	switch(e.type) {
		case SDL_KEYDOWN:
			if (e.key.repeat == 0)
				this->keydown[keyCodeFromEvent(e)]->execute();	
			break;
		case SDL_KEYUP:
			if (e.key.repeat == 0)
				this->keyup[keyCodeFromEvent(e)]->execute();
			break;
	}
}
