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
	this->offset = NULL;
}

void CollideBaseGroup::drawGroup() {
	for (CollideBase* collision: *this->group) {
		collision->draw(DrawGroup::renderer, this->offset);
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

void CollideBaseGroup::setOffset(BoundedPoint* offset) {
	this->offset = offset;
}

