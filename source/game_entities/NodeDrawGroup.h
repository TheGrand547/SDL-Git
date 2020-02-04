#pragma once
#ifndef NODE_DRAW_GROUP_H
#define NODE_DRAW_GROUP_H
#include "CollideBaseGroup.h"
#include "DrawGroup.h"
#include "../GameInstance.h"
class NodeDrawGroup;
#include "Node.h"
#include<memory>
#include<string>

class NodeDrawGroup : public DrawGroup {
	private:
		GameInstance* parent;
		std::vector<std::shared_ptr<Node>> storage;
	public:
		NodeDrawGroup(CollideBaseGroup& collision);
		~NodeDrawGroup();
		bool exists() override;
		int size() override;
		std::shared_ptr<Node>& at(int position);
		std::shared_ptr<Node>& operator[](int position);
		std::shared_ptr<Node>& getFirst();
		void clearGroup() override;
		void drawGroup() override;
		void addNullNodeAt(Point point, std::string data = "");
		void addNodeAt(Point point, std::string data = "");
		void purge(); // Remove all nodes with no connections to improve performance
		void reset();
};
#endif
