#include<string>
#include<sstream>
#include "FpsText.h"
#include "../essential/constants.h"

FpsText::FpsText(Font& font, Point position, SDL_Color color) {
	this->font = font;
	this->position = position;
	this->color = color;
	this->countedFrames = 0;
	this->averageFps = Screen::INTENDED_FRAME_RATE;
	this->timer.start();
}

FpsText::~FpsText() {}

float FpsText::getFps() {
	return this->averageFps;
}

void FpsText::draw(SDL_Renderer* renderer) {
	if (this->countedFrames > 100) {
		this->countedFrames = 1;
		this->timer.start();
	}
	this->averageFps = float(this->countedFrames) / (float(this->timer.getTicks() + 1) / 1000.f);
	this->countedFrames++;
	std::stringstream fpsStr;
	fpsStr.str("");
	fpsStr << "FPS: " << int(this->averageFps);
	this->font.drawText(this->position.x(), this->position.y(), fpsStr.str(), renderer, this->color);
}

float FpsText::getRatio() {
	return float(Screen::INTENDED_FRAME_RATE) / float(this->averageFps);
}
