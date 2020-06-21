#pragma once
#ifndef SECTOR_H
#define SECTOR_H
#include "../primitives/Line.h"
#include "../primitives/Point.h"
#include "../primitives/Polygon.h"
#include "../primitives/Rect.h"
#include<map>
#include<string>
#include<vector>

// Think of it like a "room" for path finding, will entirely replace Node/NodePath/NodeDrawGroup
class Sector {
	// TODO: Rewrite for polygon instead of rect
	public:
		Rect structure;
		std::map<Sector*, Point> pointsOfContact;
		std::string data;
		std::vector<std::weak_ptr<Sector>> attached;
	
		Sector(Rect structure, std::string data = "");
		~Sector();
		bool contains(Sector* pointer) const;
		std::string getData() const;
		void connectToOthers(std::vector<std::shared_ptr<Sector>>& others);
		void draw();
};
#endif
