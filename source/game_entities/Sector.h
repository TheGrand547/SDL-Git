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
	private:
		std::vector<Line> exits;
		std::vector<Line> solids;
	public:
		Sector();
		~Sector();
		static std::vector<Sector> MakeSectors(const std::vector<Line>& collisionLines);
};
#endif
