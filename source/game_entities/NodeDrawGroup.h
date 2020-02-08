#pragma once
#ifndef NODE_DRAW_GROUP_H
#define NODE_DRAW_GROUP_H
class NodeDrawGroup;
class GameInstance;
#include "DrawGroup.h"
#include "Node.h"
#include<memory>
#include<string>

class NodeDrawGroup : public DrawGroup {
	private:
		std::vector<std::shared_ptr<Node>> storage;
	public:
		GameInstance* parent;
		NodeDrawGroup(GameInstance* parent);
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
