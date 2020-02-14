#pragma once
#ifndef AI_NODE_H
#define AI_NODE_H
class Node;
#include "../essential/constants.h"
#include "../essential/MegaBase.h"
#include "../primitives/Point.h"
#include "../primitives/Rect.h"
#include "NodeDrawGroup.h"
#include<memory>
#include<stdlib.h>
#include<string>
#include<vector>

class GameInstance;

class Node {
	private:
		Point position;
		bool drawnThisFrame;
		std::string data;
	public:
		std::vector<std::weak_ptr<Node>> attached; // TODO: This shouldn't be public, need to make some kind of workaround
		
		Node(Point position, std::string data = "");
		~Node();
		float getDistance(const std::weak_ptr<Node> other) const;
		float getDistance(const std::shared_ptr<Node> other) const;
		float distanceToPoint(const Point point) const;
		Point getPosition() const;
		std::shared_ptr<Node> randomConnectedNode() const;
		void connectToOthers(NodeDrawGroup* parent);
		void draw();
		void reset();
		static bool checkLocationValidity(Point position, GameInstance* collision);
};
#endif
