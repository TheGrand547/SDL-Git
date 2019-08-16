#include "NodePath.h"
#include<map>
#include<algorithm>

struct VALUE {
	float value = 10000000;
};

float getValue(Node* node, Point target) {
	return target.distanceToPoint(node->getPosition());
}

NodePath::NodePath() {
}

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
		if (getValue(current, target) < 40) {
			std::map<Node*, Node*>::iterator it = path.find(current);
			while (it != path.end()) {
				this->stored.push_back(it->first->getPosition());
				it = path.find(it->second);
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

float NodePath::distance() {
	float total = 0;
	for (int i = 0; i + 1 < this->stored.size(); i++) {
		total += this->stored[i].distanceToPoint(this->stored[i + 1]);
	}
	return total;
}

void NodePath::draw() {
	for (int i = 0; i + 1 < this->stored.size(); i++) {
		Line tmp = Line(this->stored[i], this->stored[i + 1]);
		tmp.setColorChannels(0xFF, 0x00, 0x00, 0xFF);
		tmp.drawLine(MegaBase::renderer, MegaBase::offset);
	}
}

void NodePath::removeLast() {
	if (this->stored.size() > 0) {
		this->stored.pop_back();	
	}
}

Point NodePath::getFirst() {
	if (this->stored.size() > 0) {
		return this->stored.back();
	}
	return Point();
}
