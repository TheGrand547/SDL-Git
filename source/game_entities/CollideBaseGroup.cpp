#include "CollideBaseGroup.h"

CollideBaseGroup::CollideBaseGroup() {
}

CollideBaseGroup::~CollideBaseGroup() {
	this->clearGroup();
}

bool CollideBaseGroup::exists() {
	return this->group.size() > 0;
}

void CollideBaseGroup::clearGroup() {
	std::vector<CollideBase*>::iterator iter = this->group.begin();
	for (; iter != this->group.end(); iter++) {
		delete *iter;
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

bool collideRect(CollideBaseGroup& boxes, Rect rect) {
	bool result = false;
	for (int i = 0; i < boxes.size() && !result; i++) {
		result = boxes[i]->overlap(rect);
		if (result) {
			result = Rect(boxes[i]->getTopLeft() - Point(), boxes[i]->getBottomRight()).overlap(rect);
		}
	}
	return result;
}

bool collideRect(CollideBaseGroup* boxes, Rect rect) {
	return collideRect(*boxes, rect);
}

Point smallestDistanceFrom(CollideBaseGroup& boxes, Point origin, Line ray) {
	Point stored;
	for (int i = 0; i < boxes.size(); i++) {
		stored = smallerDistance(origin, boxes[i]->collideLine(ray), stored);
	}
	return stored;
}

Point smallestDistanceFrom(CollideBaseGroup* boxes, Point origin, Line ray) {
	return smallestDistanceFrom(*boxes, origin, ray);
}

Point collideTestVectorToRay(CollideBaseGroup& boxes, Line ray) {
	return smallestDistanceFrom(boxes, ray.getOrigin(), ray);
}

Point collideTestVectorToRay(CollideBaseGroup* boxes, Line ray) {
	return collideTestVectorToRay(*boxes, ray);
}

bool collideRectTest(CollideBaseGroup& vec, Rect rect) {
	return !collideRect(vec, rect);
}

bool collideRectTest(CollideBaseGroup* vec, Rect rect) {
	return collideRectTest(*vec, rect);
}

bool checkCollisionBetweenLineAndGroup(CollideBaseGroup& group, Line ray) {
	bool result = true;
	for (int i = 0; i < group.size() && result; i++) {
		result = group[i]->checkLineCollision(ray);
	}
	return result;
}

bool checkCollisionBetweenLineAndGroup(CollideBaseGroup* group, Line ray) {
	return checkCollisionBetweenLineAndGroup(*group, ray);
}

