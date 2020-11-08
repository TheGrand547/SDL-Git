#include "Controller.h"
#include "../../essential/util.h"
#include "../../GameInstance.h"

int scanCodeFromEvent(SDL_Event event) {
	return event.key.keysym.scancode;
}

Controller::Controller() : keyboard(SDL_GetKeyboardState(NULL)) {}

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
			case SDL_MOUSEBUTTONDOWN:
				std::cout << (int) mouseX << (int) mouseY << std::endl;
				break;
			case SDL_KEYDOWN:
				if (e.key.repeat == 0) {
					// TODO: This is horse shit, fix it slob
					this->cheatStream << char(tolower(*SDL_GetKeyName(e.key.keysym.sym)));
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
	for (const auto& [key, value] : this->cheatMap) {
		if (this->cheatStream.str().find(key) != std::string::npos) {
			if (value != NULL) {
				value(this->parent);
				this->cheatStream.str("");
				break;
			}
		}
	}
	for (const auto& [key, value] : this->buttons) {
		if (this->keyboard[key]) {
			if (value != NULL) value(this->parent);
		}
	}
	this->updateListeners();
}

void Controller::addButton(int value, GameCommand func) {
	this->buttons[value] = func;
}

void Controller::addButton(std::string str, GameCommand func) {
	this->buttons[this->config[str]] = func;
}

void Controller::addKey(int value, std::shared_ptr<CommandBase> command) {
	this->keys[value] = command;
}

void Controller::addListener(int key, int threshold) {
	this->listeners[key] = HeldKey(threshold);
}

void Controller::addListener(std::string key, int threshold) {
	this->addListener(this->config[key], threshold);
}

void Controller::updateListeners() {
	for(std::map<int, HeldKey>::iterator iterator = this->listeners.begin(); iterator != listeners.end(); iterator++) {
		iterator->second.set(this->keyboard[iterator->first]);
	}
}

HeldKey& Controller::checkListener(int key) {
	return this->listeners[key];
}

void Controller::addPlayerKeys() {
	// TODO: Fuck this
	this->addButton(this->config["Right"], [](GameInstance* g) {g->gameState["p_x"] += 1;});
	this->addButton(this->config["Left"],  [](GameInstance* g) {g->gameState["p_x"] -= 1;});
	this->addButton(this->config["Up"],    [](GameInstance* g) {g->gameState["p_y"] -= 1;});
	this->addButton(this->config["Down"],  [](GameInstance* g) {g->gameState["p_y"] += 1;});
}

void Controller::addCheat(std::string key, GameCommand func) {
	this->cheatMap[key] = func;
}
