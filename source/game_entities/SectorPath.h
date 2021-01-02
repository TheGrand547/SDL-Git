#pragma once
#ifndef SECTOR_PATH_H
#define SECTOR_PATH_H
#include "base/ThingBase.h"
#include "CollisionHandler.h"
#include "Sector.h"
#include <memory>
#include <vector>

typedef std::shared_ptr<SectorBase> SectorPtr;

class SectorPath {
	protected:
		std::vector<SectorPtr> stored;
		std::vector<Point> pointers;
		ThingBase* owner;
	public:
		SectorPath(ThingBase* owner);
		SectorPath& operator=(const SectorPath& that);
		~SectorPath();
		bool isFinished() const;
		int size();
		Point currentTarget(Point currentPosition);
		void clear();
		void createPath(SectorPtr startingSector, SectorPtr target);
		void createPath(Point start, Point target);
		void draw();
};
#endif
