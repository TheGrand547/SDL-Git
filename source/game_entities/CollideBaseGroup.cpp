#include "CollideBaseGroup.h"

CollideBaseGroup::CollideBaseGroup() {}

CollideBaseGroup::~CollideBaseGroup() {
	this->clearGroup();
}

bool CollideBaseGroup::exists() {
	return this->group.size() > 0;
}

void CollideBaseGroup::clearGroup() {
	std::vector<CollideBase*>::iterator iter = this->group.begin();
	for (; iter != this->group.end(); iter++) {
		delete iter[0];
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

CollideBase*& CollideBaseGroup::operator[](int index) {
	return this->group[index];
}

int CollideBaseGroup::size() {
	return this->group.size();
}

bool CollideBaseGroup::doesPlayerNotCollide(Rect rect) {
	/* True - the rect DOES collide with this collide group, given the special rules for player collision
	 * False - the rect DOESN'T collide with this collide group */
	bool result = false;
	for (int i = 0; i < this->size() && !result; i++) {
		result = this->group[i]->overlap(rect);
		if (result) {
			result = Rect(this->group[i]->getTopLeft() - Point(), this->group[i]->getBottomRight()).overlap(rect); // I hate this
		}
	}
	return !result;
}

bool CollideBaseGroup::doesCollideWith(Rect rect) {
	/* True - the rect DOES collide with this collide group
	 * False - the rect DOESN'T collide with this collide group */
	bool result = false;
	for (int i = 0; i < this->size() && !result; i++) {
		result = this->group[i]->overlap(rect);
	}
	return result;
}

bool CollideBaseGroup::doesNotCollideWith(Rect rect) {
	/* True - the rect DOESN'T collide with this collide group
	 * False - the rect DOES collide with this collide group */
	return !this->doesCollideWith(rect);
}

bool CollideBaseGroup::doesNotCollideWith(Line ray) { /** ONE OF THESE IS WRONG, FIND IT AND FIX IT**/
	/* True - the line DOESN'T collide with this collide group
	 * False - the line DOES collide with this collide group */
	bool result = true;
	for (int i = 0; i < this->size() && result; i++) {
		result = this->group[i]->checkLineCollision(ray);
	}
	return result;
}

bool CollideBaseGroup::doesCollideWith(Line ray) {
	/* True - the line DOES collide with this collide group
	 * False - the line DOESN'T collide with this collide group */
	bool result = false;
	for (int i = 0; i < this->size() && !result; i++) {
		result = this->group[i]->checkLineCollision(ray);
	}
	return result;
}

Point CollideBaseGroup::closestPointThatCollidesWith(Line ray) {
	Point stored;
	for (int i = 0; i < this->size(); i++) {
		stored = smallerDistance(ray.getOrigin(), this->group[i]->collideLine(ray), stored);
	}
	return stored;
}
