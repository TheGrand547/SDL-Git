#include "CollideBaseGroup.h"

CollideBaseGroup::CollideBaseGroup() {
}

CollideBaseGroup::~CollideBaseGroup() {
	typename std::vector<CollideBase*>::iterator it = this->group.begin();
	while (it != this->group.end()) {
		delete this->group.front();
		it = this->group.erase(it);
	}
	this->group.clear();
}

void CollideBaseGroup::drawGroup() {
	for (CollideBase* collision: this->group) {
		collision->draw(MegaBase::renderer, MegaBase::offset);
	}
}

void CollideBaseGroup::push_back(CollideBase* collision) {
	this->group.push_back(collision);
}

void CollideBaseGroup::setTexture(SuperTexture* texture) {
	for (CollideBase* collision: this->group) {
		collision->setTexture(texture);
	}
}

CollideBase* CollideBaseGroup::operator[](int index) {
	return this->group[index];
}

int CollideBaseGroup::size() {
	return this->group.size();
}

bool collideRect(Rect rect, CollideBaseGroup* boxes) {
	bool result = false;
	for (int i = 0; i < boxes->size() && !result; i++) {
		result = (*boxes)[i]->overlap(rect);
	}
	return result;
}

Point smallestDistanceFrom(CollideBaseGroup* boxes, Point origin, Line ray) {
	Point stored;
	for (int i = 0; i < boxes->size(); i++) {
		stored = smallerDistance(origin, (*boxes)[i]->collideLine(ray), stored);
	}
	return stored;
}

Point collideTestVectorToRay(CollideBaseGroup* boxes, Line ray) {
	return smallestDistanceFrom(boxes, ray.getOrigin(), ray);
}

bool collideRectTest(Rect rect, CollideBaseGroup* vec) {
	return !collideRect(rect, vec);
}

