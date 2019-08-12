#pragma once
#ifndef NODE_PATH_H
#define NODE_PATH_H
#include "Node.h"
#include<vector>

class NodePath {
	private:
		std::vector<Node*> MINE;
	public:
		NodePath();
		NodePath(Node* startingNode, Point target);
		NodePath& operator=(const NodePath& that);
		~NodePath();
		void draw();
};
#endif
