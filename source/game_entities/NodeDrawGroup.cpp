#include "NodeDrawGroup.h"

NodeDrawGroup::NodeDrawGroup() {
	this->collision = NULL;
}

NodeDrawGroup::~NodeDrawGroup() {
	this->clearGroup();
}

bool NodeDrawGroup::exists() {
	return this->storage.size() > 0;
}

void NodeDrawGroup::clearGroup() {
	std::vector<Node*>::iterator iter = this->storage.begin();
	for (; iter != this->storage.end(); iter++) {
		delete iter[0];
	}
	this->storage.clear();
}

void NodeDrawGroup::drawGroup() {
	for (Node* node: this->storage) {
		node->draw();
	}
}

Node*& NodeDrawGroup::at(int index) {
	return this->storage[index];
}

Node*& NodeDrawGroup::operator[](int index) {
	return this->storage[index];
}

Node*& NodeDrawGroup::getFirst() {
	return this->storage.front();
}

void NodeDrawGroup::addNodeAt(Point point) {
	if (Node::checkLocationValidity(point, *this->collision)) {
		Node* node = NULL;
		if (this->collision != NULL) {
			node = new Node(point, *this, *this->collision);	
		} else {
			node = new Node(point);
		}
		this->storage.push_back(node);	
	}
}

int NodeDrawGroup::size() {
	return this->storage.size();
}

void NodeDrawGroup::reset() {
	for (Node* node: this->storage) {
		node->reset();
	}
}

void NodeDrawGroup::setCollision(CollideBaseGroup& collision) {
	this->setCollision(&collision);
}

void NodeDrawGroup::setCollision(CollideBaseGroup* collision) {
	this->collision = collision;
}
