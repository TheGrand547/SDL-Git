#include "SectorGroup.h"
#include "../GameInstance.h"
#include "CollisionHandler.h"

typedef std::weak_ptr<SectorBase> WeakSectorPtr;
typedef std::vector<SectorPtr> SectorPtrVector;

SectorGroup::SectorGroup(GameInstance* parent) : DrawGroup(parent) {}

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

std::vector<SectorPtr> SectorGroup::sectorsThatTouch(const std::shared_ptr<ThingBase>& target) {
	std::vector<SectorPtr> vector;
	for (SectorPtr& sector: this->storage) {
		if (target->overlap(sector->structure())) vector.push_back(sector);
	}
	return vector;
}

void SectorGroup::addSector(Rect structure, std::string data) {
	this->storage.push_back(std::make_shared<Sector<Rect>>(structure, data));
	this->storage.back()->structure().setColorChannels(0xFF, 0xFF, 0x00, 0xFF);
}

void SectorGroup::clearGroup() {
	this->storage.clear();
}

void SectorGroup::connectSectors() {
	for (SectorPtr sector: this->storage) sector->connectToOthers(this->storage);
	for (SectorPtr sector: this->storage) sector->clean(this->storage);
}

void SectorGroup::drawGroup() {
	for (SectorPtr sector: this->storage) sector->draw(this->parent->getRenderer(), this->parent->getOffset());
}

void SectorGroup::purge() {
	LOG("Before Purging: %i Sector(s)", this->size());
	SectorPtrVector::iterator it = this->storage.begin();
	while (it != this->storage.end()) {
		if (!it[0] || it[0]->attached().size() == 0 || !it[0]->structure().isReal()) {
			it = this->storage.erase(it);
			continue;
		}
		it++;
	}
	LOG("After Purging: %i Sector(s)", this->size());
	
	for (const ThingPtr& thing: this->parent->collisionThings) {
		for (SectorPtr& sector: this->storage) {
			if (thing->overlap(sector->structure())) sector->getContained().push_back(thing);
		}
	}
}

