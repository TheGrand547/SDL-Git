#include "AlertText.h"

AlertText::AlertText(const std::string& text, Point position, SDL_Color color, int ms) : 
					done(false), position(position), message(text), duration(ms) {
	this->setColor(color);
}


AlertText::~AlertText() {}

bool AlertText::finished() const {
	return this->done;
}

void AlertText::draw(Renderer renderer) {
	if (!this->timer.isStarted()) {
		this->timer.start();
		return;
	}
	if (this->timer.getTicks() >= this->duration) {
		this->done = true;
		return;
	}
	this->font.drawText(this->position - renderer.offset, this->message, renderer.renderer, this->color);
}
