#include "AppearingText.h"
#include<string>
#include<sstream>

AppearingText::AppearingText(std::string text, float lettersPerSecond, int startingIndex, int fontSize, std::string filename, SDL_Color color, Point position, int charWrap) {
	this->text = text;
	this->charWrap = charWrap;
	this->font = new Font(fontSize, filename.c_str());
	this->ticksPerLetter = 1000 / lettersPerSecond;
	this->index = startingIndex;
	this->leftOver = 0;
	this->color = color;
	this->position = position;
}

AppearingText::AppearingText(std::string text, float lettersPerSecond, int startingIndex, Point position, SDL_Color color, Font* font, int charWrap) {
	this->text = text;
	this->charWrap = charWrap;
	this->font = font;
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
			for (int i = this->ticksPerLetter; i <= this->leftOver; i += ticksPerLetter) {
				this->index++;
			}
		}
		this->leftOver %= this->ticksPerLetter;
		this->timer.start();
		std::stringstream temp;
		temp.str("");
		for (int i = 0; i < this->index; i++) {
			temp << this->text.at(i);
		}
		if (this->charWrap) {
			this->font->renderTextWrapped(this->position.x(), this->position.y(), temp.str(), renderer, this->color, this->charWrap);
		} else {
			this->font->renderText(this->position.x(), this->position.y(), temp.str(), renderer, this->color);
		}
		return;
	}
	this->timer.start();
	this->update(renderer);
}
