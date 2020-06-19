#pragma once
#ifndef SECTOR_GROUP_H
#define SECTOR_GROUP_H
class GameInstance;
#include "../essential/random.h"
#include "DrawGroup.h"
#include "Sector.h"
#include<memory>
#include<string>
#include<utility>

typedef std::shared_ptr<Sector> SectorPtr;

class SectorGroup : public DrawGroup {
	private:
		std::vector<SectorPtr> storage;
	public:
		GameInstance* parent;
		SectorGroup(GameInstance* parent);
		~SectorGroup();
		bool exists() override;
		int size() override;
		SectorPtr& at(int position);
		SectorPtr& operator[](int position);
		SectorPtr& getFirst();
		void addSector(Rect structure, std::string data = "");
		void clearGroup() override;
		void drawGroup() override;
		void connectSectors();
		void purge();
};
#endif
