#include "AlertTextHandler.h"
#include "GameInstance.h"

AlertTextHandler::AlertTextHandler() {}

AlertTextHandler::~AlertTextHandler() {}

void AlertTextHandler::addMessage(AlertText text) {
	this->alerts.push_back(text);
}

void AlertTextHandler::draw() {
	for (uint i = 0; i < this->alerts.size(); i++) {
		this->alerts[i].draw(this->parent->getRenderer(), this->parent->getOffset());
		if (this->alerts[i].isDone()) {
			this->alerts.erase(this->alerts.begin() + i);
			i--;
		}
	}
}

