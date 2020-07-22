#include "BackgroundElement.h"

BackElement::BackElement(Point position, const std::string& type) : position(position), type(type) {}

BackElement::BackElement(const BackElement& other) {
	this->position = other.position;
	this->type = other.type;
}

BackElement::~BackElement() {}

BackElement& BackElement::operator=(BackElement& other) {
	this->position = other.position;
	this->type = other.type;
	return *this;
}

std::shared_ptr<Texture> BackElement::createGroundTexture(SDL_Renderer* renderer, const std::string& type) {
	std::shared_ptr<Texture> temp = std::make_shared<Texture>();
	temp->loadFromFile(renderer, type);
	return temp;
}
