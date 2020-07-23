#include "FpsText.h"
#include<string>
#include<sstream>
#include "../essential/constants.h"

FpsText::FpsText(Font& font, Point position, SDL_Color color) {
	this->font = font;
	this->position = position;
	this->color = color;
	this->fpsTimer.start();
	this->frameTimer.start();
}

FpsText::~FpsText() {}

float FpsText::getFps() {
	return this->fpsTimer.getFps();
}

void FpsText::draw(SDL_Renderer* renderer) {
	this->fpsTimer.tick();
	std::stringstream fpsStr;
	fpsStr.str("");
	fpsStr << "FPS: " << int(this->fpsTimer.getFps());
	this->font.drawText(this->position, fpsStr.str(), renderer, this->color);
}

float FpsText::getRatio() {
	return this->frameTimer.getTicks() / 1000.f;
}

void FpsText::drawFrameTime(SDL_Renderer* renderer) {
	std::stringstream fpsStr;
	fpsStr.str("");
	fpsStr << "Frame Time: " << this->frameTimer.getTicks() << " ms";
	this->font.drawText(this->position + Point(0, 20), fpsStr.str(), renderer, this->color);
	this->frameTimer.start();
}
