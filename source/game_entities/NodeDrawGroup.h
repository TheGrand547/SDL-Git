#pragma once
#ifndef NODE_DRAW_GROUP_H
#define NODE_DRAW_GROUP_H
#include "DrawGroup.h"
class NodeDrawGroup;
#include "Node.h"
class NodeDrawGroup : public DrawGroup {
	private:
		int a;
		std::vector<Node*> storage;
	public:
		NodeDrawGroup();
		~NodeDrawGroup();
		void drawGroup();
		Node* operator[](int position);
};
#endif
