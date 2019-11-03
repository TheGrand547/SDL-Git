#pragma once
#ifndef NODE_PATH_H
#define NODE_PATH_H
#include "Node.h"
#include "../essential/random.h"
#include<vector>

class NodePath {
	private:
		std::vector<Node*> stored;
		float storedDistance;
	public:
		NodePath();
		NodePath(Node* startingNode, Point target);
		NodePath& operator=(const NodePath& that);
		~NodePath();
		int size();
		float distance();
		Point getFirst();
		void clear();
		void draw(Point point = Point());
		void removeLast(); // To remove the last element
};
#endif
