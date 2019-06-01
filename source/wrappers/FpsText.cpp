#include<string>
#include<sstream>
#include "FpsText.h"
#include "../essential/constants.h"

FpsText::FpsText(Font* font, Point position, SDL_Color color) {
	this->font = font;
	this->position = position;
	this->color = color;
	this->countedFrames = 0;
	this->averageFps = Screen::INTENDED_FRAME_RATE;
	this->timer.start();
}

FpsText::~FpsText() {
	this->font = NULL;
}
float FpsText::getFps() {
	return this->averageFps;
}

void FpsText::draw(SDL_Renderer* renderer) {
	if (this->countedFrames > 1000) {
		this->countedFrames = 1;
		this->timer.start();
	}
	this->averageFps = this->countedFrames / ((this->timer.getTicks() + 1) / 1000.f);
	std::stringstream fpsStr;
	fpsStr.str("");
	fpsStr << "FPS: " << int(this->averageFps);
	this->font->renderText(this->position.x(), this->position.y(), fpsStr.str(), renderer, this->color);
	this->countedFrames++;
	
}

float FpsText::getRatio() {
	return Screen::INTENDED_FRAME_RATE / this->averageFps;
}
