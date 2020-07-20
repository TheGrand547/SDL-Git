#include "AppearingText.h"
#include<string>
#include<sstream>

AppearingText::AppearingText(std::string text, Font* font, Point position, double lettersPerSecond, SDL_Color color, int charWrap, int startingIndex) {
	this->font = font;
	this->text = text;
	this->charWrap = charWrap;
	this->ticksPerLetter = 1000 / lettersPerSecond;
	this->index = startingIndex;
	this->leftOver = 0;
	this->color = color;
	this->position = position;
}

AppearingText::~AppearingText() {
	this->font = NULL;
}

void AppearingText::update(SDL_Renderer* renderer) {
	if (this->timer.isStarted()) {
		this->leftOver += int(this->timer.getTicks());
		if (this->index < this->text.length()) {
			for (int i = this->ticksPerLetter; i <= this->leftOver; i += ticksPerLetter) this->index++;
		}
		this->leftOver %= this->ticksPerLetter;
		this->timer.start();
		std::stringstream temp;
		temp.str("");
		for (uint i = 0; i < this->index; i++) {
			temp << this->text.at(i);
		}
		this->font->drawText(this->position, temp.str(), renderer, this->color, this->charWrap);
		return;
	}
	this->timer.start();
	this->update(renderer);
}
