#include "NodePath.h"
#include<map>
#include<algorithm>

struct VALUE {
	float value = 10000000;
};

float getValue(Node* node, Point target) {
	return target.distanceToPoint(node->getPosition());
}

NodePath::NodePath() {}

NodePath::NodePath(Node* startingNode, Point target) {
	this->stored.clear();
	std::vector<Node*> unused = {startingNode};
	std::map<Node*, Node*> path;
	
	std::map<Node*, VALUE> cost;
	cost[startingNode].value = 0;
	
	std::map<Node*, VALUE> currentCost;
	currentCost[startingNode].value = 0;

	std::vector<Node*> closed;
	Node* current = startingNode;
	
	while (unused.size() > 0) {
		current = unused[0];
		for (Node* node: unused) {
			if (currentCost[node].value < currentCost[current].value) {
				current = node;
			}
		}
		if (getValue(current, target) < 50) {
			std::map<Node*, Node*>::iterator it = path.find(current);
			std::vector<Node*> temp;
			while (it != path.end()) {
				temp.push_back(it->first);
				it = path.find(it->second);
			}
			for (std::vector<Node*>::reverse_iterator it = temp.rbegin(); it != temp.rend(); it++) {
				this->stored.push_back(*it);
			}
			break;
		}
		unused.erase(std::find(unused.begin(), unused.end(), current));
		closed.push_back(current);
		for (Node* node: current->attached) {
			if (std::find(closed.begin(), closed.end(), node) != closed.end()) {
				continue;
			}
			if (std::find(unused.begin(), unused.end(), node) == unused.end()) {
				unused.push_back(node);
			}
			float general = cost[current].value + current->getDistance(node);
			if (general < cost[node].value) {
				path[node] = current;
				cost[node].value = general;
				currentCost[node].value = cost[node].value + getValue(node, target);
			}
		}
	}
}

NodePath::~NodePath() {}

NodePath& NodePath::operator=(const NodePath& that) {
	this->stored = that.stored;
	return *this;
}

float NodePath::distanceFrom(Node* node) {
	float total = 0;
	std::vector<Node*>::iterator i = std::find(this->stored.begin(), this->stored.end(), node);
	for (; i + 1 != this->stored.end(); i++) {
		total += i[0]->getPosition().distanceToPoint(i[1]->getPosition());
	}
	return total;
}

float NodePath::distance() {
	float total = 0;
	for (int i = 0; i + 1 < this->stored.size(); i++) {
		total += this->stored[i]->getPosition().distanceToPoint(this->stored[i + 1]->getPosition());
	}
	return total;
}

void NodePath::draw() {
	for (int i = 0; i + 1 < this->stored.size(); i++) {
		Line tmp = Line(this->stored[i]->getPosition(), this->stored[i + 1]->getPosition());
		tmp.setColorChannels(0xFF, 0x00, 0x00, 0xFF);
		tmp.drawLine(MegaBase::renderer, MegaBase::offset);
	}
}

void NodePath::removeLast() {
	if (this->stored.size() > 0) {
		this->stored.erase(this->stored.begin());	
	}
}

Node* NodePath::firstNode() {
	if (this->stored.size() > 0) {
		return this->stored.front();
	}
	return NULL;
}

Node* NodePath::lastNode() {
	if (this->stored.size() > 0) {
		return this->stored.back();
	}
	return NULL;
}

Point NodePath::getLast() {
	if (this->stored.size() > 0) {
		return this->stored.back()->getPosition();
	}
	return Point();
}

Point NodePath::getFirst() {
	if (this->stored.size() > 0) {
		return this->stored.front()->getPosition();
	}
	return Point();
}

Node* NodePath::operator[](int index) {
	if (this->stored.size() > 0) {
		if (index < this->stored.size()) {
			return this->stored[index];	
		}
	}
	return NULL;
}

void NodePath::combinePath(NodePath& other) {
	for (Node* node: other.stored) {
		if (std::find(this->stored.begin(), this->stored.end(), node) == this->stored.end()) { // Function this
			this->stored.push_back(node);	
		}
	}
}

int NodePath::size() {
	return this->stored.size();
}

void NodePath::eraseFrom(Node* node) {
	this->stored.erase(std::find(this->stored.begin(), this->stored.end(), node) + 1, this->stored.end());
}
