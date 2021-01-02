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
	return this->stored.size() <= 1;
}

int SectorPath::size() {
	return this->stored.size();
}

Point SectorPath::currentTarget(Point currentPosition) {
	Point centerDelta;
	if (!this->stored.size()) {
		TRACE("Uninitialized path");
	} else {
		centerDelta = (this->stored[0]->structure().getCenter() - currentPosition);
	}
	switch (this->stored.size()) {
		case 1: 
			// This is the end state
			if (centerDelta.getFastMagnitude() > 10) {
				return centerDelta.getUnitVector();
			}
			[[fallthrough]];
		case 0: return Point();
		default:
			// Get the point of contact between the current sector and the next sector
			Point edgePoint = this->stored[0]->pointsOfContact()[this->stored[1].get()];
			// If we are at the contact point then we need to calculate the next vector to the next point of contact
			if ((edgePoint - currentPosition).getFastMagnitude() < 5 ) {//|| (currentPosition - this->stored[1]->structure().getCenter()).getFastMagnitude() < 5) {
				this->stored.erase(this->stored.begin());
				edgePoint = this->stored[0]->pointsOfContact()[this->stored[1].get()];
			}
			// Create line between the current position and the (current) target point
			Line edge(currentPosition, edgePoint);
			// Get a simple collision box of the owner of this path
			Rect rect(this->owner->getBoundingRect());
			rect.setCenter(edge.midPoint());
			// Check if the simple collision box has to just proceeed to the center of the current setor
			if (this->owner->parent->collision->doesCollideWith(rect)) {
				return centerDelta.getUnitVector();
			}
			return (edgePoint - currentPosition).getUnitVector();
	}
}

void SectorPath::clear() {
	this->stored.clear();
}

void SectorPath::createPath(SectorPtr startingSector, SectorPtr target) {
	this->clear();
	this->stored = AStar::generatePath(startingSector, target, getValue, edgeFunction);
}
void SectorPath::createPath(Point start, Point target) {
	SectorPtr startSector = this->owner->parent->sectors.currentSector(start), endSector = this->owner->parent->sectors.currentSector(target);
	if (!startSector || !endSector) {
		LOG("One or of more of the points are not on the pathfinding grid");
		return;
	}
	this->clear();
	this->stored = AStar::generatePath(startSector, endSector, getValue, edgeFunction);
	this->pointers = {start};
	for (Uint i = 0; i + 2 < this->stored.size(); i++) {
		Point current = this->pointers.back();
		Line line(current, target);
		// Straight shot
		if (!this->owner->parent->collision->doesCollideWith(line)) break;
		if (this->stored[i]->structure().containsPoint(current)) {
			// TODO: Fill this in, you know what to do i hope <- what did this dumbass mean
		}
		//line = Line(current,);
	}
	this->pointers.push_back(target);
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
