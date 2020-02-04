#pragma once
#ifndef AI_NODE_H
#define AI_NODE_H
#include<vector>
#include<stdlib.h>
#include "../primitives/Point.h"
#include "../primitives/Rect.h"
#include "CollideBaseGroup.h"
class Node;
#include "NodeDrawGroup.h"
#include<memory>
#include<string>

class Node {
	private:
		Point position;
		bool drawnThisFrame;
		std::string data;
	public:
		std::vector<std::shared_ptr<Node>> attached; // TODO: This shouldn't be public, need to make some kind of workaround
		Node(Point position, std::string data = ""); // This is the constructor for a "null node", one that needs to be re-evaluated for calculations later
		Node(Point position, NodeDrawGroup* parent, std::string data = "");
		~Node();
		float getDistance(std::shared_ptr<Node> other);
		float distanceToPoint(Point point);
		Point getPosition();
		std::shared_ptr<Node> randomConnectedNode();
		void addAttached(std::shared_ptr<Node> node);
		void draw();
		void reset();
		static bool checkLocationValidity(Point position, CollideBaseGroup& collision);
};
#endif
