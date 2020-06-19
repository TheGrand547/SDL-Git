#include "SectorGroup.h"
#include "../GameInstance.h"
#include "CollisionHandler.h"

typedef std::weak_ptr<Sector> WeakSectorPtr;
typedef std::pair<SectorPtr, SectorPtr> sector_pair;
typedef std::vector<SectorPtr> SectorPtrVector;

SectorGroup::SectorGroup(GameInstance* parent) : parent(parent) {}

SectorGroup::~SectorGroup() {
	this->clearGroup();
}

bool SectorGroup::exists() {
	return this->storage.size() > 0;
}

int SectorGroup::size() {
	return this->storage.size();
}

SectorPtr& SectorGroup::at(int index) {
	return this->storage[index];
}

SectorPtr& SectorGroup::getFirst() {
	return this->storage.front();
}

SectorPtr& SectorGroup::operator[](int index) {
	return this->storage[index];
}

void SectorGroup::addSector(Rect structure, std::string data) {
	this->storage.push_back(std::make_shared<Sector>(structure, data));
}

void SectorGroup::clearGroup() {
	this->storage.clear();
}

void SectorGroup::connectSectors() {
	for (SectorPtr sector: this->storage) sector->connectToOthers(this->storage);
}

void SectorGroup::drawGroup() {
	for (SectorPtr sector: this->storage) sector->draw();
}

void SectorGroup::purge() {
	LOG("Before Purging Sectors: %i", this->size());
	SectorPtrVector constructionSectors;
	SectorPtrVector::iterator it = this->storage.begin();
	while (it != this->storage.end()) {
		if (!it[0] || it[0]->attached.size() == 0) {
			it = this->storage.erase(it);
			continue;
		}
		if (!it[0]->getData().compare("CONSTRUCTION")) {
			// INSERT THE CONSTRUCTION CODE
			constructionSectors.push_back(it[0]);
			//it = this->storage.erase(it); // Commented out for testing
			it++; // should be removed after testing
			continue;
		}
		it++;
	}
	LOG("After Purging Sectors: %i", this->size());
}

