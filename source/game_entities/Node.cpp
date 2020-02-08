#include "Node.h"
#include "CollisionHandler.h"

// TODO: Add functionality for data to be contained within the nodes

Node::Node(Point position, std::string data) : data(data), position(position) {
	// "Null" node, one that can be placed before collision group is fully created
	this->drawnThisFrame = false;
}

Node::Node(Point position, NodeDrawGroup* parent, std::string data) : data(data), position(position) {
	this->drawnThisFrame = false;
	for (int i = 0; i < parent->size(); i++) {
		if (this->position.distanceToPoint(parent->at(i)->position) > NODE::NODE_DISTANCE_MAX) {
			continue;
		}
		if (parent->parent->collision.doesNotCollideWith(Line(this->position, parent->at(i)->position))) {
			if (Node::checkLocationValidity(Line(this->position, parent->at(i)->position).midPoint(), parent->parent)) {
				this->attached.push_back(parent->at(i));
				parent->at(i)->addAttached(std::shared_ptr<Node>(this));
			}
		}
	}
}

Node::~Node() {}

std::shared_ptr<Node> Node::randomConnectedNode() {
	return this->attached[rand() % this->attached.size()];
}

float Node::getDistance(std::shared_ptr<Node> other) {
	return this->position.distanceToPoint(other->getPosition());
}

Point Node::getPosition() {
	return this->position;
}

void Node::reset() {
	this->drawnThisFrame = false;
}

void Node::draw() { // Legacy function only for testing purposes
	//this->drawnThisFrame = true;
	Line tempLine;
	for (std::shared_ptr<Node> node: this->attached) {
		if (!node->drawnThisFrame) {
			// BREACHING DE GATEZ
			tempLine = Line(this->position, node->position);
			tempLine.setColorChannels(0xFF, 0x00, 0x00, 0xFF);
			tempLine.drawLine(MegaBase::renderer, MegaBase::offset);
			// D - CANE
		}
	}
	Point temp = this->position - MegaBase::offset;
	circleColor(MegaBase::renderer, temp.x(), temp.y(), 10, 0xFF0000FF);
}

void Node::addAttached(std::shared_ptr<Node> node) {
	this->attached.push_back(node);
}

bool Node::checkLocationValidity(Point position, GameInstance* instance) {
	/* True -> valid location
	 * False -> invalid location */
	Rect testRect = Rect(position, 50, 50);
	testRect -= Point(testRect.getWidth(), testRect.getHeight()) / 2.0;
	return instance->collision.doesNotCollideWith(testRect);
}

float Node::distanceToPoint(Point point) {
	return this->position.distanceToPoint(point);
}
