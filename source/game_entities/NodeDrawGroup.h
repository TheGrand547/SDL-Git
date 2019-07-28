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
		bool exists() override;
		int size() override;
		Node*& operator[](int position);
		void clearGroup() override;
		void drawGroup() override;
		void add(Node* node);
		void reset();
};
#endif
