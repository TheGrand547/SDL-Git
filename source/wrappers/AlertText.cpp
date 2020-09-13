#include "AlertText.h"

AlertText::AlertText(const std::string& text, Point position, SDL_Color color, int textSize, int ms, const std::string& filename) : 
					done(false), duration(ms), position(position), color(color), message(text) {
	this->font.loadFont(textSize, filename.c_str());
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
