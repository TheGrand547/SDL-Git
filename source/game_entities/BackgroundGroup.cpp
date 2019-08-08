#include "BackgroundGroup.h"

BackgroundGroup::BackgroundGroup() {}

BackgroundGroup::~BackgroundGroup() {
	for (std::map<Ground::Type, Texture*>::iterator iter = this->textures.begin(); iter != this->textures.end(); iter++) {
		delete iter->second;
	}
	this->clearGroup();
}

bool BackgroundGroup::exists() {
	return this->elements.size() > 0;
}

int BackgroundGroup::size() {
	return this->elements.size();
}

void BackgroundGroup::clearGroup() {
	for (std::vector<BackElement*>::iterator iter = this->elements.begin(); iter != this->elements.end(); iter++) {
		delete *iter;
	}
	this->elements.clear();
}

void BackgroundGroup::add(Point position, Ground::Type type) {
	if (this->textures[type] == NULL) {
		this->textures[type] = BackElement::createGroundTexture(MegaBase::renderer, type);
		this->textures[type]->normalizeTexture(MegaBase::renderer);
		this->textures[type]->testFilter();
	}
	this->elements.push_back(new BackElement(position, type));
	this->elements.back()->setTexture(this->textures[type]);
	
}

void BackgroundGroup::drawGroup() {
	for (BackElement* element: this->elements) {
		element->draw(MegaBase::renderer, MegaBase::offset);
	}
}
