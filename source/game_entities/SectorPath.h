#pragma once
#ifndef SECTOR_PATH_H
#define SECTOR_PATH_H
#include "Sector.h"
#include "../essential/random.h"
#include<memory>
#include<vector>

typedef std::shared_ptr<SectorBase> SectorPtr;
class GameInstance;

class SectorPath {
	protected:
		std::vector<SectorPtr> stored;
	public:
		GameInstance* parent; // TODO: Remove bandaid
		SectorPath();
		SectorPath(SectorPtr start, SectorPtr end);
		SectorPath& operator=(const SectorPath& that);
		~SectorPath();
		bool finished() const;
		int size();
		Point currentTarget(Point currentPosition);
		void clear();
		void draw();
		void getPath(SectorPtr startingSector, SectorPtr target);
};
#endif
