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
	this->MINE.clear();
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
		if (getValue(current, target) < 20) {
			std::map<Node*, Node*>::iterator it = path.find(current);
			while (it != path.end()) {
				this->MINE.push_back(it->first);
				it = path.find(it->second);
			}
			return;
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
	
	/*
	std::cout << depth << std::endl;
	depth++;
	this->end = NULL;
	this->start = startingNode;
	if (depth > 2) {
		this->end = this->start;
		this->next = NULL;
		return;
	}
	std::vector<NodePath> ohboy;
	for (Node* node: startingNode->attached) {
		if (node == previous) {
			continue;
		}
		if (node->getPosition().distanceToPoint(target) < desiredDistance) {
			// This means we've reached the end, and must go back up the chain
			std::cout << "GOING UP" << std::endl;
			this->end = node;
			break;
		}
		std::cout << this->start->getPosition() << std::endl;
		ohboy.push_back(NodePath(node, target, desiredDistance, startingNode, depth));
	}
	std::cout << "Options done at level -> " << depth << std::endl;
	NodePath min = ohboy[0];
	if (ohboy.size() > 1) {
		for (NodePath nodePath: ohboy) {
			if (nodePath.distance() < min.distance()) {
				std::cout << ":(" << std::endl;
				min = nodePath;
				std::cout << ":D" << std::endl;
			}
		}
	}
	this->end = min.start;
	std::cout << "End of this NodePath" << std::endl;*/
}

NodePath::~NodePath() {}

NodePath& NodePath::operator=(const NodePath& that) {
	this->MINE = that.MINE;
	return *this;
}

void NodePath::draw() {
	for (int i = 0; i < this->MINE.size() - 1; i++) {
		Line tmp = Line(this->MINE[i]->getPosition(), this->MINE[i + 1]->getPosition());
		tmp.setColorChannels(0xFF, 0x00, 0x00, 0xFF);
		tmp.drawLine(MegaBase::renderer, MegaBase::offset);
	}
}
