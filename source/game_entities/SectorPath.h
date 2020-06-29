#pragma once
#ifndef SECTOR_PATH_H
#define SECTOR_PATH_H
#include "Sector.h"
#include "../essential/random.h"
#include<memory>
#include<vector>

typedef std::shared_ptr<SectorBase> SectorPtr;

class SectorPath {
	protected:
		bool stage;
		int index;
		std::vector<SectorPtr> stored;
	public:
		SectorPath();
		SectorPath(SectorPtr start, SectorPtr end);
		SectorPath& operator=(const SectorPath& that);
		~SectorPath();
		bool finished() const;
		int size();
		Point currentTarget(Point currentPosition);
		void clear();
		void draw();
};
#endif
