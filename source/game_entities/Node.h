#pragma once
#ifndef AI_NODE_H
#define AI_NODE_H
#include<vector>
#include "../primitives/Point.h"
#include "../primitives/Rect.h"
#include "CollideBaseGroup.h"
#include "NodeDrawGroup.h"
class Node {
	private:
		std::vector<Node*> attached;
		Point position;
	public:
		Node(Point position, NodeDrawGroup* group);
		~Node();
		void draw();
};
#endif
