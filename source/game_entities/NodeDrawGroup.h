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

typedef std::shared_ptr<Node> NodePtr;

class NodeDrawGroup : public DrawGroup {
	private:
		friend class Node;
		std::vector<NodePtr> storage;
		bool addNodesOnLine(const Line line);
	public:
		GameInstance* parent;
		NodeDrawGroup(GameInstance* parent);
		~NodeDrawGroup();
		bool addNodeAt(Point point, std::string data = "");
		bool exists() override;
		int size() override;
		NodePtr& at(int position);
		NodePtr& operator[](int position);
		NodePtr& getFirst();
		void clearGroup() override;
		void drawGroup() override;
		void connectNodes();
		void purge(); // Remove all nodes with no connections to improve performance
		void reset();
};
#endif
