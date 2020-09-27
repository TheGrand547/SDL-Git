#include "SectorPath.h"
#include <algorithm>
#include <map>
#include <unordered_map>
#include <unordered_set>

typedef std::shared_ptr<SectorBase> SectorPtr;
typedef std::vector<SectorPtr> SectorVector;
typedef std::unordered_set<SectorPtr> SectorSet;
typedef std::map<double, SectorPtr> SectorSet2;


namespace std {
	template<> struct hash<SectorPtr> {
		std::size_t operator()(const SectorPtr& thing) const noexcept {
			return std::hash<Point>{}(thing->structure().getCenter());
		}
	};
}

struct VALUE {
	double value = 10000000;
};

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
			if (this->owner->parent->collision.doesCollideWith(rect)) {
				return centerDelta.getUnitVector();
			}
			// Shelved for now
			/*
			if (this->stored.size() > 1) {
				edge = Line(currentPosition, this->stored[1]->structure().getCenter());
				rect.setCenter(edge.midPoint());
				if (!this->owner->parent->collision.doesCollideWith(rect) && !this->owner->parent->collision.doesCollideWith(edge)) {
					std::cout << (currentPosition - this->stored[1]->structure().getCenter()) << std::endl;
					return (this->stored[1]->structure().getCenter() - currentPosition).getUnitVector();
				}
			}*/
			return (edgePoint - currentPosition).getUnitVector();
	}
}

void SectorPath::clear() {
	this->stored.clear();
}

void SectorPath::createPath(SectorPtr startingSector, SectorPtr target) {
	// A* implementation
	this->clear();
	if (startingSector.get() == target.get()) return;
	if (startingSector->contains(target.get())) {
		this->stored = {startingSector, target};
		return;
	}
	
	SectorSet2 unused = {{0, startingSector}};
	std::map<SectorPtr, SectorPtr> path;
	path[startingSector] = NULL;
	
	std::map<SectorPtr, VALUE> cost;
	cost[startingSector].value = 0;
	
	std::map<SectorPtr, VALUE> currentCost;
	currentCost[startingSector].value = 0;

	SectorSet closed;
	SectorPtr current = startingSector;
	double dub = 0;
	while (unused.size() > 0) {
		auto g = unused.begin();
		dub = g->first;
		current = g->second;
		if (current == target) {
			SectorVector temp;
			std::map<SectorPtr, SectorPtr>::iterator it = path.find(current);
			while (it != path.end()) {
				temp.push_back(it->first);
				it = path.find(it->second);
			}
			SectorVector::reverse_iterator iter = temp.rbegin();
			for (; iter != temp.rend(); iter++) {
				this->stored.push_back(iter[0]);
			}
			break;
		}
		unused.erase(g);
		closed.insert(current);
		for (std::weak_ptr<SectorBase> weak: current->attached()) {
			SectorPtr node = weak.lock();
			if (!node) continue;
			double general = cost[current].value + edgeFunction(node, current);
			if (general < cost[node].value) {
				path[node] = current;
				cost[node].value = general;
				currentCost[node].value = cost[node].value + getValue(node, target);
				if (unused.find(general) == unused.end()) unused[general] = node; 
			}
		}
	}
}


void SectorPath::draw() {
	for (uint i = 0; i + 1 < this->stored.size(); i++) {
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
