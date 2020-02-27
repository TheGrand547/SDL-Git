#pragma once
#ifndef NODE_DRAW_GROUP_H
#define NODE_DRAW_GROUP_H
class NodeDrawGroup;
class GameInstance;
#include "../essential/random.h"
#include "DrawGroup.h"
#include "Node.h"
#include<memory>
#include<string>
#include<utility>

class NodeDrawGroup : public DrawGroup {
	private:
		friend class Node;
		std::vector<std::shared_ptr<Node>> storage;
		bool addNodesOnLine(const Line line);
	public:
		GameInstance* parent;
		NodeDrawGroup(GameInstance* parent);
		~NodeDrawGroup();
		bool addNodeAt(Point point, std::string data = "");
		bool exists() override;
		int size() override;
		std::shared_ptr<Node>& at(int position);
		std::shared_ptr<Node>& operator[](int position);
		std::shared_ptr<Node>& getFirst();
		void clearGroup() override;
		void drawGroup() override;
		void connectNodes();
		void purge(); // Remove all nodes with no connections to improve performance
		void reset();
};
#endif
