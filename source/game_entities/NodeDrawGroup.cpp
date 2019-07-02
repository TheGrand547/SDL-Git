#include "NodeDrawGroup.h"

NodeDrawGroup::NodeDrawGroup() {}

NodeDrawGroup::~NodeDrawGroup() {}

void NodeDrawGroup::drawGroup() {}

Node* NodeDrawGroup::operator[](int index) {
	return this->storage[index];
}
