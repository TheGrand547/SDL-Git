#include "NodeDrawGroup.h"
#include "../GameInstance.h"
#include "CollisionHandler.h"
typedef std::pair<std::shared_ptr<Node>, std::shared_ptr<Node>> node_pair;
typedef std::shared_ptr<Node> NodePtr;

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

bool NodeDrawGroup::addNodeAt(Point point, std::string data) {
	if (Node::checkLocationValidity(point, this->parent)) {
		for (std::shared_ptr<Node> node: this->storage) {
			if (point.distanceToPoint(node->getPosition()) < 25) {
				// TODO: Log invalid node at
				return false;
			}
		}
		this->storage.push_back(std::make_shared<Node>(point, data));
		return true;
	} else {
		return false;
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
					/*
					if (node->numberOfSharedNodes(otherNode) == 1) {
						Point reverse1 = node->getPosition().onlyX() + otherNode->getPosition().onlyY();
						Point reverse2 = node->getPosition().onlyY() + otherNode->getPosition().onlyX();
						this->addNodesOnLine(Line(reverse1, reverse2));
					}*/
				} else {
					if (node->numberOfSharedNodes(otherNode) == 1) {
						Point reverse1 = node->getPosition().onlyX() + otherNode->getPosition().onlyY();
						Point reverse2 = node->getPosition().onlyY() + otherNode->getPosition().onlyX();
						this->addNodesOnLine(Line(reverse1, reverse2));
					}
				}
			}
		}
	}
	int ctr = 0;
	std::vector<node_pair> barred;
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
					// Add midpoints
					if (lineA.isParallel(lineB) && !lineA.isCollinear(lineB)) {
						/*
						Point reverse1 = pair.first->getPosition().onlyX() + pair.second->getPosition().onlyY();
						Point reverse2 = pair.first->getPosition().onlyY() + pair.second->getPosition().onlyX();
						this->addNodesOnLine(Line(reverse1, reverse2));*/
						/*
						Point points[] = {Line(lineA.midPoint(), lineB.midPoint()).midPoint(), 
							Line(lineA.getOrigin(), lineB.getOrigin()).midPoint(),
							Line(lineA.getEnd(),lineB.getEnd()).midPoint()};
						for (Point point: points) {
							if (this->addNodeAt(point, std::string("p"))) {
								ctr++;
							}
						}*/
						if (lineA.midPoint().distanceToPoint(lineB.midPoint()) > 150) {
							// Since the distances is not insignificant
							this->addNodeAt(pair.first->getPosition());
							this->addNodeAt(pair.second->getPosition());
							this->addNodeAt(otherPair.first->getPosition());
							this->addNodeAt(otherPair.second->getPosition());
						} else {
							//this->addNodeAt(Line(lineA.midPoint(), lineB.midPoint()).midPoint());
						}
					}
					// Add corners
				}
		}
	}
	for (NodePtr f: this->storage) {
		f->attached.clear();
		f->connectToOthers(this);
	}
	
	it = this->storage.begin();
	std::vector<node_pair> ignore;
	while (it != this->storage.end()) {
		bool g = false;
		for (std::weak_ptr<Node> ptr: it[0]->attached) {
			if (NodePtr node = ptr.lock()) {
				if (node->shareAllNodes(it[0])) {
					g = !g;
					it = this->storage.erase(it);
					//it++;
					break;
				}
			}
		}
		/*
		for (node_pair f: HAHA) {
			if (valueInVector<node_pair>(ignore, f)) continue;
			if (Line(f.first->getPosition(), f.second->getPosition()).isPointOnThisLine(it[0]->getPosition())) {
				if (f.first->getPosition() == it[0]->getPosition() || f.second->getPosition() == it[0]->getPosition()) {
					continue;
				}
				std::cout << f.first->getPosition() << " AND " << f.second->getPosition() << " KILL " << it[0]->getPosition() << std::endl;
				it = this->storage.erase(it);
				g = !g;
				ignore.push_back(f);
				break;
			}
		}*/
		
		if (!g) {
			it++;
		}
	}
	std::cout << "Nodes: " << this->storage.size() << std::endl;
	std::cout << "Midpoints: " << ctr << std::endl;
	std::cout << "Pairs: " << HAHA.size() << std::endl;
}

void NodeDrawGroup::connectNodes() {
	for (std::shared_ptr<Node> node: this->storage) {
		node->connectToOthers(this);
	}
}

bool NodeDrawGroup::addNodesOnLine(const Line line) {
	return this->addNodeAt(line.getOrigin()) && this->addNodeAt(line.getEnd());
}
