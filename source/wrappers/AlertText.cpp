#include "AlertText.h"

AlertText::AlertText(std::string text, Point position, SDL_Color color, int textSize, float milliseconds, std::string filename) {
	this->message = text;
	this->position = position;
	this->color = color;
	this->font = Font(textSize, filename.c_str());
	this->finished = false;
	this->maxMilliseconds = milliseconds;
}

AlertText::~AlertText() {}

AlertText::AlertText(const AlertText& other) {
	this->message = other.message;
	this->position = other.position;
	this->color = other.color;
	this->font = other.font;
	this->finished = other.finished;
	this->maxMilliseconds = other.maxMilliseconds;
}

AlertText& AlertText::operator=(const AlertText& other) {
	this->message = other.message;
	this->position = other.position;
	this->color = other.color;
	this->font = other.font;
	this->finished = other.finished;
	this->maxMilliseconds = other.maxMilliseconds;
	return *this;
}

void AlertText::draw(SDL_Renderer* renderer, Point offset) {
	if (!this->timer.isStarted()) {
		this->timer.start();
		return;
	}
	if (this->timer.getTicks() >= this->maxMilliseconds) {
		this->finished = true;
		return;
	}
	this->font.drawText(this->position - offset, this->message, renderer, this->color);
}

bool AlertText::isDone() {
	return this->finished;
}
