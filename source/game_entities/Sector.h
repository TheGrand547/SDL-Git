#pragma once
#ifndef SECTOR_H
#define SECTOR_H
#include<vector>
#include "../primitives/Line.h"
#include "../primitives/Point.h"
#include "../primitives/Polygon.h"
#include "../primitives/Rect.h"

// Think of it like a "room" for path finding
class Sector {
	protected:
		// TODO: Rewrite for polygon instead of rect
		Rect structure;
		std::vector<std::weak_ptr<Sector>> attached;
	public:
		Sector(Rect structure);
		~Sector();
		bool contains(Sector* pointer) const;
		Line iwannaline();
		void connectToOthers(std::vector<std::shared_ptr<Sector>>& others);
};
#endif
