#include "BackgroundGroup.h"
#include "../GameInstance.h"

BackgroundGroup::BackgroundGroup(GameInstance* parent) : DrawGroup(parent) {}

BackgroundGroup::~BackgroundGroup() {
	this->clearGroup();
}

bool BackgroundGroup::exists() {
	return this->elements.size() > 0;
}

int BackgroundGroup::size() {
	return this->elements.size();
}

void BackgroundGroup::clearGroup() {
	this->elements.clear();
}

void BackgroundGroup::add(Point position, const std::string& type) {
	if (this->textures[type] == NULL) {
		this->textures[type] = BackElement::createGroundTexture(this->parent->getRenderer(), type);
		this->textures[type]->normalizeTexture(MegaBase::renderer);
	}
	this->elements.push_back(std::make_shared<BackElement>(position, type));
	this->elements.back()->setTexture(this->textures[type]);
	
}

void BackgroundGroup::drawGroup() {
	for (std::shared_ptr<BackElement>& element: this->elements) {
		element->draw(this->parent->getRenderer(), this->parent->getOffset());
	}
}

void BackgroundGroup::setParent(GameInstance& parent) {
	this->parent = &parent;
}
