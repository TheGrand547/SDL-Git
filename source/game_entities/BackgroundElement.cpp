#include "BackgroundElement.h"

BackElement::BackElement() {
	this->position = Point();
	this->type = Ground::GRASS;
	this->texture = NULL;
}

BackElement::BackElement(Rect rect, Ground::Type type) {
	this->position = Point(rect.getTopLeft());
	this->type = type;
	this->texture = NULL;
}

BackElement::BackElement(Point position, Ground::Type type) {
	this->position = Point(position);
	this->type = type;
	this->texture = NULL;
}

BackElement::BackElement(const BackElement& other) {
	this->position = other.position;
	if (this->texture != NULL) {
		delete this->texture;
	}
	this->texture = other.texture;
	this->type = other.type;
}

BackElement::~BackElement() {
	this->texture = NULL;
}

BackElement& BackElement::operator=(BackElement& other) {
	this->position = other.position;
	this->type = other.type;
	if (this->texture != NULL) {
		delete this->texture;
	}
	this->texture = other.texture;
	return *this;
}

void BackElement::setTexture(Texture* texture) {
	this->texture = texture;
}

void BackElement::draw(SDL_Renderer* renderer, Point offset) {
	if (this->texture != NULL) {
		this->texture->setPos(this->position);
		this->texture->draw(renderer, offset);
	}
}

Texture* BackElement::createGroundTexture(SDL_Renderer* renderer, Ground::Type type, int width, int height) {
	Texture* temp = new Texture();
	temp->loadFromFile(Ground::filenames[type], renderer, width, height);
	return temp;
}

void BackElement::createGroundTexture(SDL_Renderer* renderer, Texture* texture, Ground::Type type, int width, int height) {
	texture->loadFromFile(Ground::filenames[type], renderer, width, height);
}
