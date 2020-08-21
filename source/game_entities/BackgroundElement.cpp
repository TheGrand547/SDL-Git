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

std::shared_ptr<Surface> BackElement::createGroundTexture(const std::string& type) {
	std::shared_ptr<Surface> temp = std::make_shared<Surface>();
	temp->load(type);
	return temp;
}
