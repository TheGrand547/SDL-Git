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
	protected:
		// TODO: Rewrite for polygon instead of rect
		Rect structure;
		std::string data;
		std::map<Sector*, Point> pointsOfContact;
	public:
		std::vector<std::weak_ptr<Sector>> attached;
	
		Sector(Rect structure, std::string data = "");
		~Sector();
		bool contains(Sector* pointer) const;
		Line iwannaline();
		std::string getData() const;
		void connectToOthers(std::vector<std::shared_ptr<Sector>>& others);
		void draw();
};
#endif
