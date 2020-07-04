#include "BackgroundElement.h"

BackElement::BackElement(Point position, const std::string& type) : position(position), type(type) {}

BackElement::BackElement(const BackElement& other) {
	this->position = other.position;
	this->texture = other.texture;
	this->type = other.type;
}

BackElement::~BackElement() {
	this->texture = NULL;
}

BackElement& BackElement::operator=(BackElement& other) {
	this->position = other.position;
	this->type = other.type;
	this->texture = other.texture;
	return *this;
}

void BackElement::setTexture(std::shared_ptr<Texture> texture) {
	this->texture = texture;
}

void BackElement::draw(SDL_Renderer* renderer, Point offset) {
	if (this->texture) this->texture->draw(renderer, this->position - offset);
}

std::shared_ptr<Texture> BackElement::createGroundTexture(SDL_Renderer* renderer, const std::string& type) {
	std::shared_ptr<Texture> temp = std::make_shared<Texture>();
	temp->loadFromFile(renderer, type);
	return temp;
}
