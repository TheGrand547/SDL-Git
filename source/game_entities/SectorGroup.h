#pragma once
#ifndef SECTOR_GROUP_H
#define SECTOR_GROUP_H

class GameInstance;

#include "DrawGroup.h"
#include "Sector.h"
#include <memory>

typedef std::shared_ptr<SectorBase> SectorPtr;

class SectorGroup : public DrawGroup {
	private:
		std::vector<SectorPtr> storage;
	public:
		SectorGroup(GameInstance* parent);
		~SectorGroup();
		bool exists() override;
		int size() override;
		SectorPtr& at(int position);
		SectorPtr& operator[](int position);
		SectorPtr& getFirst();
		SectorPtr currentSector(const std::shared_ptr<ThingBase>& target);
		std::vector<SectorPtr> allSectors(const std::shared_ptr<ThingBase>& target);
		void clearGroup() override;
		void drawGroup() override;
		void connectSectors();
		void purge();

		template<typename T, typename... Args> SectorPtr createSector(Args... args) {
			SectorPtr sector = std::make_shared<Sector<T>>(T(args...));
			this->storage.push_back(sector);
			sector->structure().setColorChannels(0xFF, 0xFF, 0x00, 0xFF);
			return sector;
		}
};
#endif
