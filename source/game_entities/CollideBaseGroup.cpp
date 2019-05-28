#include "CollideBaseGroup.h"

CollideBaseGroup::CollideBaseGroup() {
	this->group = new std::vector<CollideBase*>;
}

CollideBaseGroup::~CollideBaseGroup() {
	typename std::vector<CollideBase*>::iterator it = this->group->begin();
	while (it != this->group->end()) {
		delete this->group->front();
		it = this->group->erase(it);
	}
	this->group->clear();
	delete group;
}

void CollideBaseGroup::drawGroup(SDL_Renderer* renderer, BoundedPoint& screenPosition) {
	for (CollideBase* collision: *this->group) {
		collision->draw(renderer, screenPosition);
	}
}

void CollideBaseGroup::push_back(CollideBase* collision) {
	this->group->push_back(collision);
}

void CollideBaseGroup::setTexture(SuperTexture* texture) {
	for (CollideBase* collision: *this->group) {
		collision->setTexture(texture);
	}
}

std::vector<CollideBase*>* CollideBaseGroup::get() {
	return this->group;
}

CollideBase* CollideBaseGroup::operator[](int index) {
	return (*this->group)[index];
}

int CollideBaseGroup::size() {
	return this->group->size();
}
