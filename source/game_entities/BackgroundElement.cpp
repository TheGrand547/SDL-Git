#include "BackgroundElement.h"

BackElement::BackElement(Rect rect, std::string type) : texture(NULL), type(type) {
	this->structure = (rect.isAxisAligned()) ? rect : rect.getBoundingRect();
}

BackElement::BackElement(const BackElement& other) {
	this->structure = other.structure;
	this->texture = other.texture;
	this->type = other.type;
}

BackElement::~BackElement() {
	this->texture = NULL;
}

BackElement& BackElement::operator=(BackElement& other) {
	this->structure = other.structure;
	this->type = other.type;
	this->texture = other.texture;
	return *this;
}

void BackElement::setTexture(std::shared_ptr<Texture> texture) {
	this->texture = texture;
}

void BackElement::draw(SDL_Renderer* renderer, Point offset) {
	if (this->texture) this->texture->draw(renderer, this->structure.getTopLeft() - offset);
}

std::shared_ptr<Texture> BackElement::createGroundTexture(SDL_Renderer* renderer, std::string type) {
	std::shared_ptr<Texture> temp = std::make_shared<Texture>();
	temp->loadFromFile(renderer, type);
	return temp;
}
