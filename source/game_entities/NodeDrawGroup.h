#pragma once
#ifndef NODE_DRAW_GROUP_H
#define NODE_DRAW_GROUP_H
#include "DrawGroup.h"
#include "CollideBaseGroup.h"
class NodeDrawGroup;
#include "Node.h"

class NodeDrawGroup : public DrawGroup {
	private:
		CollideBaseGroup* collision;
		std::vector<Node*> storage;
	public:
		NodeDrawGroup();
		~NodeDrawGroup();
		bool exists() override;
		int size() override;
		Node*& at(int position);
		Node*& operator[](int position);
		Node*& getFirst();
		void clearGroup() override;
		void drawGroup() override;
		void addNullNodeAt(Point point);
		void addNodeAt(Point point);
		void purge(); // Remove all nodes with no connections to improve performance
		void reset();
		void setCollision(CollideBaseGroup& collision);
		void setCollision(CollideBaseGroup* collision);
};
#endif
