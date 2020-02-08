#include "NodeDrawGroup.h"
#include "../GameInstance.h"

NodeDrawGroup::NodeDrawGroup(GameInstance* parent) : parent(parent) {}

NodeDrawGroup::~NodeDrawGroup() {
	this->clearGroup();
}

bool NodeDrawGroup::exists() {
	return this->storage.size() > 0;
}

void NodeDrawGroup::clearGroup() {
	this->storage.clear();
}

void NodeDrawGroup::drawGroup() {
	for (std::shared_ptr<Node> node: this->storage) {
		node->draw();
	}
}

std::shared_ptr<Node>& NodeDrawGroup::at(int index) {
	return this->storage[index];
}

std::shared_ptr<Node>& NodeDrawGroup::operator[](int index) {
	return this->storage[index];
}

std::shared_ptr<Node>& NodeDrawGroup::getFirst() {
	return this->storage.front();
}

void NodeDrawGroup::addNodeAt(Point point, std::string data) {
	if (Node::checkLocationValidity(point, this->parent)) {
		std::shared_ptr<Node> node;
		if (this->parent->collision.size() > 0) {
			node = std::make_shared<Node>(point, this, data);	
		} else {
			node = std::make_shared<Node>(point, data);
		}
		this->storage.push_back(node);	
	} else {
		// TODO: Log invalid node at (Point)
	}
}

void NodeDrawGroup::addNullNodeAt(Point point, std::string data) {
	std::shared_ptr<Node> node = std::make_shared<Node>(point, data);
	this->storage.push_back(node);	
}

int NodeDrawGroup::size() {
	return this->storage.size();
}

void NodeDrawGroup::reset() {
	for (std::shared_ptr<Node> node: this->storage) {
		node->reset();
	}
}

void NodeDrawGroup::purge() {
	for (std::shared_ptr<Node> node: this->storage) {
		if (node->attached.size() == 0) {
			std::vector<std::shared_ptr<Node>>::iterator it = std::find(this->storage.begin(), this->storage.end(), node);
			if (it != this->storage.end()) {
				this->storage.erase(it);
			}	
		}
	}
}
