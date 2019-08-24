#pragma once
#ifndef NODE_PATH_H
#define NODE_PATH_H
#include "Node.h"
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
		float distanceFrom(Node* start);
		float distanceFromWithPoint(Node* start, Point target);
		Point getLast();
		Point getFirst();
		Node* operator[](int index);
		Node* firstNode();
		Node* lastNode();
		void eraseFrom(Node* begin);
		void combinePath(NodePath& other);
		void draw(Point point = Point());
		void removeLast(); // To remove the last element
};
#endif
