#include "Node.h"
#include "../essential/MegaBase.h"

Node::Node(Point position) {
	// "Null" node, one that can be placed before collision group is fully created
	this->drawnThisFrame = false;
	this->position = position;
}

Node::Node(Point position, NodeDrawGroup& group, CollideBaseGroup& collision) {
	this->drawnThisFrame = false;
	this->position = position;
	for (int i = 0; i < group.size(); i++) {
		if (this->position.distanceToPoint(group[i]->position) > 100) {
			continue;
		}
		if (checkCollisionBetweenLineAndGroup(collision, Line(this->position, group[i]->position))) {
			if (Node::checkLocationValidity(Line(this->position, group[i]->position).midPoint(), collision)) {
				this->attached.push_back(group[i]);
				group[i]->addAttached(this);
			}
		}
	}
}

Node::~Node() {}

Node* Node::randomConnectedNode() {
	return this->attached[rand() % this->attached.size()];
}

float Node::getDistance(Node* other) {
	return this->position.distanceToPoint(other->getPosition());
}

Point Node::getPosition() {
	return this->position;
}

void Node::reset() {
	this->drawnThisFrame = false;
}

void Node::draw() {
	//this->drawnThisFrame = true;
	Line tempLine;
	for (Node* node: this->attached) {
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

void Node::addAttached(Node* node) {
	this->attached.push_back(node);
}

bool Node::checkLocationValidity(Point position, CollideBaseGroup& collision) {
	/* True -> valid location
	 * False -> invalid location */
	Rect testRect = Rect(position, 50, 50);
	testRect -= Point(testRect.getWidth(), testRect.getHeight()) / 2.0;
	return collideRectTest(collision, testRect);
}

