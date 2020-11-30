#include "FpsText.h"
#include "../essential/constants.h"
#include <string>
#include <sstream>

FpsText::FpsText(Point position, SDL_Color color) : position(position) {
	this->setColor(color);
	this->fpsTimer.start();
	this->frameTimer.start();
}

FpsText::~FpsText() {}

bool FpsText::finished() const {
	return false;
}

double FpsText::getFps() const {
	return this->fpsTimer.getFps();
}

void FpsText::draw(Renderer renderer) {
	this->fpsTimer.tick();
	std::stringstream fpsStr;
	fpsStr << "FPS: " << int(this->fpsTimer.getFps());
	this->font.drawText(this->position, fpsStr.str(), renderer.renderer, this->color);
}

void FpsText::drawFrameTime(Renderer renderer) {
	std::stringstream fpsStr;
	fpsStr << "Frame Time: " << this->frameTimer.getTicks() << " ms";
	this->font.drawText(this->position + Point(0, 20), fpsStr.str(), renderer.renderer, this->color);
	this->frameTimer.start();
}
