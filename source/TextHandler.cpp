#include "TextHandler.h"
#include "GameInstance.h"

TextHandler::TextHandler() {}

TextHandler::~TextHandler() {}

void TextHandler::draw() {
	TextVector::iterator iter = this->stored.begin();
	while (iter != this->stored.end()) {
		iter[0]->draw(this->parent->getRenderer());
		if (iter[0]->finished()) iter = this->stored.erase(iter);
		else iter++;
	}
}

