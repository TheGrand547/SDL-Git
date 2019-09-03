#include "NodePath.h"
#include<map>
#include<algorithm>

struct VALUE {
	float value = 10000000;
};

float getValue(Node* node, Point target) {
	return node->distanceToPoint(target);
}

NodePath::NodePath() {}

NodePath::NodePath(Node* startingNode, Point target) {
	this->storedDistance = 0;
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
		if (getValue(current, target) < NODE::NODE_DISTANCE_MAX) {
			std::vector<Node*> temp;
			std::map<Node*, Node*>::iterator it = path.find(current);
			while (it != path.end()) {
				temp.push_back(it->first);
				it = path.find(it->second);
			}
			std::vector<Node*>::reverse_iterator iter = temp.rbegin();
			for (; iter != temp.rend(); iter++) {
				this->stored.push_back(iter[0]);
			}
			break;
		}
		unused.erase(std::find(unused.begin(), unused.end(), current));
		closed.push_back(current);
		for (Node* node: current->attached) {
			if (valueInVector(closed, node)) {
				continue;
			}
			if (valueNotInVector(unused, node)) {
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
	this->storedDistance = that.storedDistance;
	return *this;
}

// TODO: Figure out if these are ever necessary
float NodePath::distanceFrom(Node* node) {
	float total = 0;
	std::vector<Node*>::iterator i = std::find(this->stored.begin(), this->stored.end(), node);
	for (; i[0] != this->stored.back(); i++) {
		total += i[0]->getDistance(i[1]);
	}
	return total;
}

float NodePath::distance() {
	if (this->storedDistance == 0) {
		this->storedDistance = 0;
		for (int i = 0; i + 1 < this->stored.size(); i++) {
			this->storedDistance += this->stored[i]->distanceToPoint(this->stored[i + 1]->getPosition());
		}	
	}
	return this->storedDistance;
}

void NodePath::draw(Point point) {
	if (point.isReal()) {
		Line tmp = Line(this->stored[0]->getPosition(), point);
		tmp.setColorChannels(0xFF, 0x00, 0x00, 0xFF);
		tmp.drawLine(MegaBase::renderer, MegaBase::offset);
	}
	std::vector<Node*>::iterator it = this->stored.begin();
	for (; it[0] != this->stored.back(); it++) {
		Line tmp = Line(it[0]->getPosition(), it[1]->getPosition());
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
		if (valueNotInVector(this->stored, node)) {
			this->stored.push_back(node);	
		}
	}
}

int NodePath::size() {
	return this->stored.size();
}

void NodePath::eraseFrom(Node* node) {
	this->stored.erase(std::find(this->stored.begin(), this->stored.end(), node) + 1, this->stored.end());
	this->stored.pop_back();
}
