#include "NodeDrawGroup.h"

NodeDrawGroup::NodeDrawGroup() {}

NodeDrawGroup::~NodeDrawGroup() {}

void NodeDrawGroup::drawGroup() {
	for (Node* node: this->storage) {
		node->draw();
	}
}

Node* NodeDrawGroup::operator[](int index) {
	return this->storage[index];
}
void NodeDrawGroup::add(Node* node) {
	this->storage.push_back(node);
}

int NodeDrawGroup::size() {
	return this->storage.size();
}

void NodeDrawGroup::reset() {
	for (Node* node: this->storage) {
		node->reset();
	}
}
