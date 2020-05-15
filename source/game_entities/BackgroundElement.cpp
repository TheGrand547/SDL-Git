#include "BackgroundElement.h"

BackElement::BackElement() {
	this->position = Point();
	this->type = Ground::filenames[Ground::GRASS];
	this->texture = NULL;
}

BackElement::BackElement(Rect rect, std::string type) {
	this->position = Point(rect.getTopLeft());
	this->type = type;
	this->texture = NULL;
}

BackElement::BackElement(Point position, std::string type) {
	this->position = Point(position);
	this->type = type;
	this->texture = NULL;
}

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
	if (this->texture != NULL) {
		this->texture->draw(renderer, this->position - offset);
	}
}

std::shared_ptr<Texture> BackElement::createGroundTexture(SDL_Renderer* renderer, std::string type, int width, int height) {
	std::shared_ptr<Texture> temp = std::make_shared<Texture>();
	temp->loadFromFile(renderer, type, width, height);
	return temp;
}

void BackElement::createGroundTexture(SDL_Renderer* renderer, std::shared_ptr<Texture> texture, std::string type, int width, int height) {
	texture->loadFromFile(renderer, type, width, height);
}
