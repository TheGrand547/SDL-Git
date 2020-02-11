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
		std::vector<std::shared_ptr<Node>> attached; // TODO: This shouldn't be public, need to make some kind of workaround
		Node(Point position, std::string data = ""); // This is the constructor for a "null node", one that needs to be re-evaluated for calculations later
		Node(Point position, NodeDrawGroup* parent, std::string data = "");
		~Node();
		float getDistance(std::shared_ptr<Node> other) const;
		float distanceToPoint(Point point) const;
		Point getPosition() const;
		std::shared_ptr<Node> randomConnectedNode() const;
		void addAttached(std::shared_ptr<Node> node);
		void draw();
		void reset();
		static bool checkLocationValidity(Point position, GameInstance* collision);
};
#endif
