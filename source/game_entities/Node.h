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
class Node {
	private:
		Point position;
		bool drawnThisFrame;
	public:
		std::vector<Node*> attached;
		Node(Point position); // This is the constructor for a "null node" aka one that needs to be re-evaluated later
		Node(Point position, NodeDrawGroup& group, CollideBaseGroup& collision);
		~Node();
		Node* randomConnectedNode();
		Point getPosition();
		float getDistance(Node* other);
		void draw();
		void reset();
		void addAttached(Node* node);
		static bool checkLocationValidity(Point position, CollideBaseGroup& collision);
};
#endif
