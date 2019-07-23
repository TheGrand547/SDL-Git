#include "AlertTextHandler.h"

AlertTextHandler::AlertTextHandler() {}

AlertTextHandler::~AlertTextHandler() {}

void AlertTextHandler::addMessage(AlertText text) {
	this->alerts.push_back(text);
}

void AlertTextHandler::drawHandler() {
	for (int i = 0; i < this->alerts.size(); i++) {
		this->alerts[i].render();
		if (this->alerts[i].isDone()) {
			this->alerts.erase(this->alerts.begin() + i);
			i--;
		}
	}
}

