#include "SectorGroup.h"
#include "../essential/misc.h"
#include "../GameInstance.h"
#include "CollisionHandler.h"

#include <utility>

typedef std::shared_ptr<SectorBase> SectorPtr;
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

SectorPtr SectorGroup::currentSector(const Point& target) const {
	SectorPtr value = NULL;
	for (const SectorPtr& sector: this->storage) {
		if (sector->structure().containsPoint(target) && (value == NULL || value->structure().getArea() > sector->structure().getArea())) value = sector;
	}
	return value;
}

SectorPtr SectorGroup::currentSector(const std::shared_ptr<ThingBase>& target) const {
	SectorPtr value = NULL;
	for (const SectorPtr& sector: this->storage) {
		if (target->overlap(sector->structure()) && (value == NULL || value->structure().getArea() > sector->structure().getArea())) value = sector;
	}
	return value;
}

std::vector<SectorPtr> SectorGroup::allSectors(const std::shared_ptr<ThingBase>& target) const {
	// TODO: Make it so this is only calculated at MOST once per frame
	std::vector<SectorPtr> vector;
	for (const SectorPtr& sector: this->storage) {
		if (target->overlap(sector->structure())) vector.push_back(sector);
	}
	return vector;
}

void SectorGroup::clearGroup() {
	this->storage.clear();
}

void SectorGroup::connectSectors() {
	for (SectorPtr sector: this->storage) sector->connectToOthers(this->storage);
	for (SectorPtr sector: this->storage) sector->clean(this->storage);
}

void SectorGroup::drawGroup() {
	for (SectorPtr sector: this->storage) sector->draw(this->parent->getRenderer());
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

