#pragma once
#ifndef NODE_DRAW_GROUP_H
#define NODE_DRAW_GROUP_H
#include "DrawGroup.h"
class NodeDrawGroup;
#include "Node.h"
class NodeDrawGroup : public DrawGroup {
	private:
		std::vector<Node*> storage;
	public:
		NodeDrawGroup();
		~NodeDrawGroup();
		int size();
		void drawGroup();
		void add(Node* node);
		void reset();
		Node* operator[](int position);
};
#endif
