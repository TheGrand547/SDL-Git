#pragma once
#ifndef AI_NODE_H
#define AI_NODE_H
#include<vector>
#include "../primitives/Point.h"
#include "../primitives/Rect.h"
#include "CollideBaseGroup.h"
class Node;
#include "NodeDrawGroup.h"
class Node {
	private:
		std::vector<Node*> attached;
		Point position;
		bool drawnThisFrame;
	public:
		Node(Point position, NodeDrawGroup* group, CollideBaseGroup* collision);
		~Node();
		void draw();
		void reset();
		void addAttached(Node* node);
		static bool checkLocationValidity(Point position, CollideBaseGroup* collision);
};
#endif
