#include "AlertText.h"
#include "../essential/MegaBase.h"
AlertText::AlertText(std::string text, Point position, SDL_Color color, int textSize, float milliseconds, std::string filename) {
	this->message = text;
	this->position = position;
	this->color = color;
	this->font = Font(textSize, filename.c_str());
	this->finished = false;
	this->maxMilliseconds = milliseconds;
}

AlertText::~AlertText() {}

void AlertText::render() {
	if (!this->timer.isStarted()) {
		this->timer.start();
		return;
	}
	if (this->timer.getTicks() >= this->maxMilliseconds) {
		this->finished = true;
		return;
	}
	this->font.renderText(this->position.x() - MegaBase::offset->x(), this->position.y() - MegaBase::offset->y(), this->message, MegaBase::renderer, this->color);
}

bool AlertText::isDone() {
	return this->finished;
}
