#include "SectorPath.h"
#include "../essential/misc.h"
#include "../Astar.h"
#include "../GameInstance.h"
#include <algorithm>
#include <map>

typedef std::shared_ptr<SectorBase> SectorPtr;
typedef std::vector<SectorPtr> SectorVector;

namespace std {
	template<> struct hash<SectorPtr> {
		std::size_t operator()(const SectorPtr& thing) const noexcept;
	};
}

double getValue(SectorPtr sector, SectorPtr target) {
	return sector->structure().getCenter().fastDistanceToPoint(target->structure().getCenter()) * ((sector->contains(target.get()) ? .25 : 1));
}

double edgeFunction(SectorPtr sector, SectorPtr target) {
	return sector->pointsOfContact()[target.get()].fastDistanceToPoint(target->structure().getCenter());
}

SectorPath::SectorPath(ThingBase* owner) : owner(owner) {}

SectorPath::~SectorPath() {
	this->clear();
}

SectorPath& SectorPath::operator=(const SectorPath& that) {
	if (this != &that) {
		this->stored.clear();
		this->owner = that.owner;
		this->stored = that.stored;
	}
	return *this;
}

bool SectorPath::isFinished() const {
	return this->pointers.size();
}

int SectorPath::size() {
	return this->stored.size();
}

Point SectorPath::currentTarget(Point currentPosition) {
	Point value;
	if (!this->pointers.size()) {
		TRACE("Path is Finished");
	} else {
		if (currentPosition.fastDistanceToPoint(this->pointers[0]) > 1) {
			if (this->pointers.size() > 2 && CollisionHandler::overlapTest(this->owner->shared_from_this(), Line(currentPosition, this->pointers[1]))) 
				this->pointers.erase(this->pointers.begin());
			value = (this->pointers[0] - currentPosition).getUnitVector();
		} else {
			//std::cout << "Going deeper" << std::endl;
			this->pointers.erase(this->pointers.begin());
			value = this->currentTarget(currentPosition);
		}
	}
	return value;
}

void SectorPath::clear() {
	this->stored.clear();
}

void SectorPath::createPath(SectorPtr startingSector, SectorPtr target) {
	this->clear();
	this->stored = AStar::generatePath(startingSector, target, getValue, edgeFunction);
	this->pointers = {startingSector->structure().getCenter()};
	
	// TODO: Function this or something idk
	for (uint i = 1; i + 1 < this->stored.size(); i++) {
		if (i != 0) {
			this->pointers.push_back(this->stored[i - 1]->pointsOfContact()[this->stored[i].get()]);
		}
		this->pointers.push_back(this->stored[i]->structure().getCenter());
	}
	this->pointers.push_back(target->structure().getCenter());
	for (std::vector<Point>::iterator i = this->pointers.begin(); i + 1 != this->pointers.end(); i++) {
		for (std::vector<Point>::iterator j = this->pointers.end()--; j != i + 2; j--) {
			if (CollisionHandler::overlapTest(NULL, Line(*i, *j))) {
				i = this->pointers.erase(i + 1, j - 1);
				break;
			}
		}
	}
}
void SectorPath::createPath(Point start, Point target) {
	SectorPtr startSector = this->owner->parent->sectors.currentSector(start), endSector = this->owner->parent->sectors.currentSector(target);
	if (!startSector || !endSector) {
		LOG("One or of more of the points are not on the pathfinding grid");
		return;
	}
	this->clear();
	this->stored = AStar::generatePath(startSector, endSector, getValue, edgeFunction);
	this->pointers = {};
	//std::cout << this->stored.size() << std::endl;
	for (uint i = 0; i + 1 < this->stored.size(); i++) {
		//std::cout << "Gamer" << std::endl;
		if (i != 0) this->pointers.push_back(this->stored[i]->structure().getCenter());
		this->pointers.push_back(this->stored[i + 1]->pointsOfContact()[this->stored[i].get()]);
	}
	this->pointers.push_back(target);
	// TODO: Something fucky is up here, dunno what
	if (this->pointers.size() > 4) {
		for (std::vector<Point>::iterator i = this->pointers.begin(); i != this->pointers.end(); i++) {
			for (std::vector<Point>::iterator j = this->pointers.end()--; j != i + 1; j--) {
				if (CollisionHandler::overlapTest(NULL, Line(*i, *j))) {
					auto q = i;
					for (; q != j; q++) {
						std::cout << *q << " ";
					}
					std::cout << std::endl;
					i = this->pointers.erase(i + 1, j - 1);
					break;
				}
			}
			//if (i == this->pointers.end()) break;
		}
	}
}


void SectorPath::draw() {
	for (Uint i = 0; i + 1 < this->stored.size(); i++) {
		Line p(this->stored[i]->structure().getCenter(), this->stored[i]->pointsOfContact()[this->stored[i + 1].get()]);
		p.setColor(0xFF, 0x00, 0xFF, 0xFF);
		p.draw(this->owner->parent->getRenderer());
		if (i != 0) {
			Line g(this->stored[i]->structure().getCenter(), this->stored[i - 1]->pointsOfContact()[this->stored[i].get()]);
			g.setColor(0xFF, 0x00, 0xFF, 0xFF);
			g.draw(this->owner->parent->getRenderer());
			Line pe(this->stored[i]->structure().getCenter(), this->stored[i]->pointsOfContact()[this->stored[i - 1].get()]);
			pe.setColor(0xFF, 0xFF, 0xFF, 0xFF);
			pe.draw(this->owner->parent->getRenderer());
		}
	}
	for (SectorPtr& sec: this->stored) {
		sec->structure().setColorChannels(0xFF, 0x00, 0x00, 0xFF);
		sec->draw(this->owner->parent->getRenderer());
	}
}

std::size_t std::hash<SectorPtr>::operator()(const SectorPtr& thing) const noexcept {
	return std::hash<Point>{}(thing->structure().getCenter());
}
