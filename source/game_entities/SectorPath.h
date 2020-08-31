#pragma once
#ifndef SECTOR_PATH_H
#define SECTOR_PATH_H
#include "Sector.h"
#include "base/ThingBase.h"
#include "../essential/random.h"
#include "../GameInstance.h"
#include<memory>
#include<vector>

typedef std::shared_ptr<SectorBase> SectorPtr;

class SectorPath {
	protected:
		std::vector<SectorPtr> stored;
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
		void draw();
};
#endif
