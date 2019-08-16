#pragma once
#ifndef NODE_PATH_H
#define NODE_PATH_H
#include "Node.h"
#include<vector>

class NodePath {
	private:
		std::vector<Point> stored; 
	public:
		NodePath();
		NodePath(Node* startingNode, Point target);
		NodePath& operator=(const NodePath& that);
		~NodePath();
		float distance();
		Point getFirst();
		void draw();
		void removeLast(); // To remove the last element
};
#endif
