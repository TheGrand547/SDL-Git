#pragma once
#ifndef NODE_PATH_H
#define NODE_PATH_H
#include "Node.h"
#include "../essential/random.h"
#include<memory>
#include<vector>

class NodePath {
	private:
		std::vector<std::shared_ptr<Node>> stored;
		float storedDistance;
	public:
		NodePath();
		NodePath(std::shared_ptr<Node> startingNode, Point target);
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
