#include "Node.h"
#include "CollisionHandler.h"
#include "../GameInstance.h"


Node::Node(Point position, std::string data) : data(data), position(position) {
	this->drawnThisFrame = false;
}

Node::~Node() {
	this->attached.clear();
}

std::shared_ptr<Node> Node::randomConnectedNode() const {
	return this->attached[rand() % this->attached.size()].lock();
}

float Node::getDistance(const std::shared_ptr<Node> other) const {
	return this->position.distanceToPoint(other->getPosition());
}

float Node::getDistance(const std::weak_ptr<Node> other) const {
	std::shared_ptr<Node> temp = other.lock();
	if (!temp) {
		// TODO: LOG ERROR
		std::cout << "ERROR: std::weak_ptr<Node> was invalid." << std::endl;
		return 0.0 / 0.0;
	}
	return this->position.distanceToPoint(temp->getPosition());
}

Point Node::getPosition() const {
	return this->position;
}

void Node::reset() {
	this->drawnThisFrame = false;
}

void Node::draw() { // Legacy function only for testing purposes
	//this->drawnThisFrame = true;
	Line tempLine;
	for (std::weak_ptr<Node> node: this->attached) {
		//std::shared_ptr<Node> temp = node.lock();
		if (auto temp = node.lock()) {
			tempLine = Line(this->position, temp->position);
			tempLine.setColorChannels(0xFF, 0x00, 0x00, 0xFF);
			tempLine.drawLine(MegaBase::renderer, MegaBase::offset);
		}
		/*
		if (!node.lock() && !temp->drawnThisFrame) {
			// BREACHING DE GATEZ
			tempLine = Line(this->position, temp->position);
			tempLine.setColorChannels(0xFF, 0x00, 0x00, 0xFF);
			tempLine.drawLine(MegaBase::renderer, MegaBase::offset);
			// D - CANE
		}*/
	}
	Point temp = this->position - *MegaBase::offset;
	circleColor(MegaBase::renderer, temp.x(), temp.y(), 10, 0xFF0000FF);
}

bool Node::checkLocationValidity(Point position, GameInstance* instance) {
	/* True -> valid location
	 * False -> invalid location */
	Rect testRect = Rect(position, 50, 50);
	testRect -= Point(testRect.getWidth(), testRect.getHeight()) / 2.0;
	return instance->collision.doesNotCollideWith(testRect);
}

float Node::distanceToPoint(const Point point) const {
	return this->position.distanceToPoint(point);
}

void Node::connectToOthers(NodeDrawGroup* parent) {
	for (std::shared_ptr<Node> node: parent->storage) {
		if (node.get() == this) continue;
		/*
		if (this->position.distanceToPoint(node->position) > NODE::NODE_DISTANCE_MAX || node.get() == this) {
			continue;
		}*/
		if (parent->parent->collision.doesNotCollideWith(Line(this->position, node->position))) {
			if (Node::checkLocationValidity(Line(this->position, node->position).midPoint(), parent->parent)) {
				this->attached.push_back(node);
			}
		}
	}
}

std::string Node::getData() const {
	return this->data;
}
