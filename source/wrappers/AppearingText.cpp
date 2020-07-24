#include "AppearingText.h"
#include<string>
#include<sstream>

AppearingText::AppearingText(std::string text, Point position, double lettersPerSecond, SDL_Color color, int charWrap, int startingIndex) : 
							charWrap(charWrap), leftOver(0), ticksPerLetter(1000 / lettersPerSecond), position(position), color(color), text(text), index(startingIndex) {
	this->timer.start();
}

AppearingText::~AppearingText() {}

bool AppearingText::finished() const {
	return false;
}

void AppearingText::draw(SDL_Renderer* renderer, Point offset) {
	// TODO: Seems inefficient, find out why
	this->leftOver += int(this->timer.getTicks());
	if (this->index < this->text.length()) {
		for (int i = this->ticksPerLetter; i <= this->leftOver; i += ticksPerLetter) this->index++;
	}
	this->leftOver %= this->ticksPerLetter;
	this->timer.start();
	std::stringstream temp;
	temp.str("");
	for (Uint i = 0; i < this->index; i++) { // Exception was caught here, investigate
		temp << this->text.at(i);
	}
	this->font.drawText(this->position - offset, temp.str(), renderer, this->color, this->charWrap);
}
