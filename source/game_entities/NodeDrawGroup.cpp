#include "NodeDrawGroup.h"
#include "../GameInstance.h"
#include "CollisionHandler.h"
typedef std::weak_ptr<Node> WeakNodePtr;
typedef std::pair<NodePtr, NodePtr> node_pair;
typedef std::vector<NodePtr> NodePtrVector;

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
	for (NodePtr node: this->storage) {
		node->draw();
	}
}

NodePtr& NodeDrawGroup::at(int index) {
	return this->storage[index];
}

NodePtr& NodeDrawGroup::operator[](int index) {
	return this->storage[index];
}

NodePtr& NodeDrawGroup::getFirst() {
	return this->storage.front();
}

bool NodeDrawGroup::addNodeAt(Point point, std::string data) {
	if (Node::checkLocationValidity(point, this->parent)) {
		for (NodePtr node: this->storage) {
			if (point.distanceToPoint(node->getPosition()) < 25) {
				return false;
			}
		}
		this->storage.push_back(std::make_shared<Node>(point, data));
		return true;
	} else {
		return false;
	}
	
}


int NodeDrawGroup::size() {
	return this->storage.size();
}

void NodeDrawGroup::reset() {
	for (NodePtr node: this->storage) {
		node->reset();
	}
}

void NodeDrawGroup::purge() {
	LOG("Before Purging Nodes: %i", this->size());
	NodePtrVector constructionNodes;
	NodePtrVector::iterator it = this->storage.begin();
	while (it != this->storage.end()) {
		if (!it[0] || it[0]->attached.size() == 0) {
			it = this->storage.erase(it);
			continue;
		}
		if (!it[0]->getData().compare("CONSTRUCTION")) {
			// INSERT THE CONSTRUCTION CODE
			constructionNodes.push_back(it[0]);
			//it = this->storage.erase(it); // Commented out for testing
			it++; // should be removed after testing
			continue;
		}
		it++;
	}
	LOG("After Purging Nodes: %i", this->size());
}

void NodeDrawGroup::connectNodes() {
	for (NodePtr node: this->storage) node->connectToOthers(this);
}

bool NodeDrawGroup::addNodesOnLine(const Line line) {
	return this->addNodeAt(line.getOrigin()) && this->addNodeAt(line.getEnd());
}
