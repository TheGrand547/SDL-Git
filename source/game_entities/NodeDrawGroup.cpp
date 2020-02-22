#include "NodeDrawGroup.h"
#include "../GameInstance.h"
#include "CollisionHandler.h"
typedef std::pair<std::shared_ptr<Node>, std::shared_ptr<Node>> node_pair;

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
		for (std::shared_ptr<Node> node: this->storage) {
			if (point.distanceToPoint(node->getPosition()) < 15) {
				// TODO: Log invalid node at
				return;
			}
		}
		this->storage.push_back(std::make_shared<Node>(point, data));	
	} else {
		// TODO: Log invalid node at (Point)
	}
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
	std::vector<std::shared_ptr<Node>> constructionNodes;
	std::vector<std::shared_ptr<Node>>::iterator it = this->storage.begin();
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
	std::vector<node_pair> HAHA;
	for (std::shared_ptr<Node> node: constructionNodes) {
		for (std::shared_ptr<Node> otherNode: constructionNodes) {
			if (node.get() != otherNode.get()) {
				if (node->isAttachedTo(otherNode) && node->getDistance(otherNode) > 50) { // CHECK THEY CAN SEE EACH OTHER
					bool flag = true;
					for (node_pair pair : HAHA) {
						if (pair.first.get() == otherNode.get() && pair.second.get() == node.get()) {
							flag = false;
							break;
						}
					}
					if (flag) {
						HAHA.push_back(std::make_pair(node, otherNode));
					}
				}
			}
		}
	}
	int ctr = 0;
	for (node_pair pair : HAHA) {
		for (node_pair otherPair : HAHA) {
			Line lineA(pair.first->getPosition(), pair.second->getPosition());
			Line lineB(otherPair.first->getPosition(), otherPair.second->getPosition());
			if (shareNoElements<Node>(pair, otherPair) &&
				pair.first->isAttachedTo(otherPair.first) &&
				pair.second->isAttachedTo(otherPair.first) &&
				pair.first->isAttachedTo(otherPair.second) &&
				pair.second->isAttachedTo(otherPair.second) &&
				lineA.intersectionPoint(lineB).isNull()) { // HAHA HAHAHHA HAH HA HH HA A
					ctr++;
				}
		}
	}
	std::cout << "Nodes: " << this->storage.size() << std::endl;
	std::cout << "Counter: " << ctr << std::endl;
	std::cout << "Pairs: " << HAHA.size() << std::endl;
}

void NodeDrawGroup::connectNodes() {
	for (std::shared_ptr<Node> node: this->storage) {
		node->connectToOthers(this);
	}
}
