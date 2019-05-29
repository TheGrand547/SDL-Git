#include "BackgroundGroup.h"

BackgroundGroup::BackgroundGroup() {}

BackgroundGroup::~BackgroundGroup() {
	for (std::map<Ground::Type, Texture*>::iterator iter = this->textures.begin(); iter != this->textures.end(); iter++) {
		delete iter->second;
	}
}

void BackgroundGroup::add(Point position, Ground::Type type) {
	if (this->textures[type] == NULL) {
		this->textures[type] = BackElement::createGroundTexture(DrawGroup::renderer, type);
	}
	this->elements.push_back(new BackElement(position, type));
	this->elements.back()->setTexture(this->textures[type]);
	
}

void BackgroundGroup::drawGroup(BoundedPoint& screenPosition) {
	for (BackElement* element: this->elements) {
		element->draw(DrawGroup::renderer, screenPosition);
	}
}
