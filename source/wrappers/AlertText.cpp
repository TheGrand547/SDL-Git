#include "AlertText.h"

AlertText::AlertText(const std::string& text, Point position, SDL_Color color, int textSize, float ms, const std::string& filename) : 
					done(false), duration(ms), position(position), color(color), message(text) {
	this->font.loadFont(textSize, filename.c_str());
}

AlertText::~AlertText() {}

void AlertText::draw(SDL_Renderer* renderer, Point offset) {
	if (!this->timer.isStarted()) {
		this->timer.start();
		return;
	}
	if (this->timer.getTicks() >= this->duration) {
		this->done = true;
		return;
	}
	this->font.drawText(this->position - offset, this->message, renderer, this->color);
}

bool AlertText::finished() const {
	return this->done;
}
