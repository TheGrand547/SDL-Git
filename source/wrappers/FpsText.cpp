#include<string>
#include<sstream>
#include "FpsText.h"
#include "../essential/constants.h"

FpsText::FpsText(Font& font, Point position, SDL_Color color) {
	this->font = font;
	this->position = position;
	this->color = color;
	this->timer.start();
	this->timer2.start();
}

FpsText::~FpsText() {}

float FpsText::getFps() {
	return this->timer.getFps();
}

void FpsText::draw(SDL_Renderer* renderer) {
	this->timer.tick();
	std::stringstream fpsStr;
	fpsStr.str("");
	fpsStr << "FPS: " << int(this->timer.getFps());
	this->font.drawText(this->position.x(), this->position.y(), fpsStr.str(), renderer, this->color);
}

float FpsText::getRatio() {
	return float(Screen::INTENDED_FRAME_RATE) / float(this->timer.getFps());
}

void FpsText::drawFrameTime(SDL_Renderer* renderer) {
	std::stringstream fpsStr;
	fpsStr.str("");
	fpsStr << "Frame Time: " << this->timer2.getTicks() / 1000.f;
	this->font.drawText(this->position.x(), this->position.y() + 20, fpsStr.str(), renderer, this->color);
	this->timer2.start();
}
