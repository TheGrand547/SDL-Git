#include "NodePath.h"
#include<map>
#include<algorithm>

struct VALUE {
	double value = 10000000;
};

double getValue(std::shared_ptr<Node> node, Point target) {
	return node->distanceToPoint(target);
}

NodePath::NodePath() {}

NodePath::NodePath(std::shared_ptr<Node> startingNode, Point target) {
	this->storedDistance = 0;
	this->stored.clear();
	std::vector<std::shared_ptr<Node>> unused = {startingNode};
	std::map<std::shared_ptr<Node>, std::shared_ptr<Node>> path;
	
	std::map<std::shared_ptr<Node>, VALUE> cost;
	cost[startingNode].value = 0;
	
	std::map<std::shared_ptr<Node>, VALUE> currentCost;
	currentCost[startingNode].value = 0;

	std::vector<std::shared_ptr<Node>> closed;
	std::shared_ptr<Node> current = startingNode;
	int counted = 0;
	while (unused.size() > 0) {
		counted++;
		current = unused[0];
		for (std::shared_ptr<Node> node: unused) {
			if (currentCost[node].value < currentCost[current].value) {
				current = node;
			}
		}
		if (getValue(current, target) < NODE::NODE_DISTANCE_MAX) {
			std::vector<std::shared_ptr<Node>> temp;
			std::map<std::shared_ptr<Node>, std::shared_ptr<Node>>::iterator it = path.find(current);
			while (it != path.end()) {
				temp.push_back(it->first);
				it = path.find(it->second);
			}
			std::vector<std::shared_ptr<Node>>::reverse_iterator iter = temp.rbegin();
			for (; iter != temp.rend(); iter++) {
				this->stored.push_back(iter[0]);
			}
			break;
		}
		unused.erase(std::find(unused.begin(), unused.end(), current));
		closed.push_back(current);
		for (std::weak_ptr<Node> weak: current->attached) {
			std::shared_ptr<Node> node = weak.lock();
			if (!node || valueInVector(closed, node)) continue;
			if (valueNotInVector(unused, node)) unused.push_back(node);
			double general = cost[current].value + current->getDistance(node);
			if (general < cost[node].value) {
				path[node] = current;
				cost[node].value = general;
				currentCost[node].value = cost[node].value + getValue(node, target);
			}
		}
	}
	//if (!this->stored.size()) {std::cout << "C" << counted << std::endl;} else {std::cout << this->stored.size() << std::endl;}
}

NodePath::~NodePath() {}

NodePath& NodePath::operator=(const NodePath& that) {
	this->stored = that.stored;
	this->storedDistance = that.storedDistance;
	return *this;
}

Point NodePath::getFirst() {
	if (this->stored.size() > 0) {
		return this->stored.front()->getPosition();
	}
	return Point();
}

void NodePath::removeLast() {
	if (this->stored.size() > 0) {
		this->stored.erase(this->stored.begin());	
	}
}

void NodePath::clear() {
	this->stored.erase(this->stored.begin(), this->stored.end());
}

float NodePath::distance() {
	if (this->storedDistance == 0) {
		this->storedDistance = 0;
		for (uint i = 0; i + 1 < this->stored.size(); i++) {
			this->storedDistance += this->stored[i]->distanceToPoint(this->stored[i + 1]->getPosition());
		}	
	}
	return this->storedDistance;
}

void NodePath::draw(Point point) {
	//if (!this->stored.size()) return;
	
	if (point.isReal()) {
		Line tmp = Line(this->stored[0]->getPosition(), point);
		tmp.setColorChannels(0xFF, 0x00, 0x00, 0xFF);
		tmp.drawLine(MegaBase::renderer, *MegaBase::offset);
	}
	if (this->stored.size() > 1) {
		std::vector<std::shared_ptr<Node>>::iterator it = this->stored.begin();
		for (; it[0] != this->stored.back(); it++) {
			Line tmp = Line(it[0]->getPosition(), it[1]->getPosition());
			tmp.setColorChannels(0xFF, 0x00, 0x00, 0xFF);
			tmp.drawLine(MegaBase::renderer, *MegaBase::offset);
		}
	}
}
