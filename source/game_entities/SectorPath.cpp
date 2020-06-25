#include "SectorPath.h"
#include "../essential/MegaBase.h"
#include<map>
#include<algorithm>

typedef std::shared_ptr<Sector> SectorPtr;

struct VALUE {
	double value = 10000000;
};

double getValue(SectorPtr sector, SectorPtr target) {
	return sector->structure.getCenter().fastDistanceToPoint(target->structure.getCenter()) * ((sector->contains(target.get()) ? .25 : 1));
}

SectorPath::SectorPath() : stage(false), index(0) {}

SectorPath::SectorPath(SectorPtr startingSector, SectorPtr target) : stage(false), index(0) {
	if (startingSector.get() == target.get()) return;
	this->stored.clear();
	std::vector<SectorPtr> unused = {startingSector};
	std::map<SectorPtr, SectorPtr> path;
	
	std::map<SectorPtr, VALUE> cost;
	cost[startingSector].value = 0;
	
	std::map<SectorPtr, VALUE> currentCost;
	currentCost[startingSector].value = 0;

	std::vector<SectorPtr> closed;
	SectorPtr current = startingSector;
	while (unused.size() > 0) {
		current = unused[0];
		for (SectorPtr node: unused) {
			if (currentCost[node].value < currentCost[current].value) {
				current = node;
			}
		}
		if (current == target) {
			std::vector<SectorPtr> temp;
			std::map<SectorPtr, SectorPtr>::iterator it = path.find(current);
			while (it != path.end()) {
				temp.push_back(it->first);
				it = path.find(it->second);
			}
			std::vector<SectorPtr>::reverse_iterator iter = temp.rbegin();
			this->stored.push_back(startingSector); // This *shouldn't* be necessary but it appears to be for the time being
			for (; iter != temp.rend(); iter++) {
				this->stored.push_back(iter[0]);
			}
			break;
		}
		unused.erase(std::find(unused.begin(), unused.end(), current));
		closed.push_back(current);
		for (std::weak_ptr<Sector> weak: current->attached) {
			SectorPtr node = weak.lock();
			if (!node || valueInVector(closed, node)) continue;
			if (valueNotInVector(unused, node)) unused.push_back(node);
			double general = cost[current].value + getValue(node, current);
			if (general < cost[node].value) {
				path[node] = current;
				cost[node].value = general;
				currentCost[node].value = cost[node].value + getValue(node, target);
			}
		}
	}
}

SectorPath::~SectorPath() {}

SectorPath& SectorPath::operator=(const SectorPath& that) {
	if (this != &that) {
		this->stored.clear();
		this->stored = that.stored;
		this->index = that.index;	
		this->stage = that.stage;
	}
	return *this;
}

bool SectorPath::finished() const {
	return this->stored.size() == (uint)this->index;
}

int SectorPath::size() {
	return this->stored.size();
}

Point SectorPath::currentTarget(Point currentPosition) {
	if (!this->stored.size()) return Point();
	if ((this->stored[index]->pointsOfContact[this->stored[index + 1].get()] - currentPosition).getFastMagnitude() < 5) {
		this->index++;
		this->stage = false;
	}
	if (!this->stage && this->index != 0) {
		if (currentPosition.distanceToPoint(this->stored[index]->structure.getCenter()) < 2.5) this->stage = true;
		return (this->stored[index]->structure.getCenter() - currentPosition).getUnitVector();
	}
	return (this->stored[index]->pointsOfContact[this->stored[index + 1].get()] - currentPosition).getUnitVector();
}

void SectorPath::clear() {
	this->stored.clear();
}

void SectorPath::draw() {
	for (uint i = 0; i + 1 < this->stored.size(); i++) {
		Line p(this->stored[i]->structure.getCenter(), this->stored[i]->pointsOfContact[this->stored[i + 1].get()]);
		p.setColor(0xFF, 0x00, 0xFF, 0xFF);
		p.drawLine(MegaBase::renderer, *MegaBase::offset);
		if (i != 0) {
			Line g(this->stored[i]->structure.getCenter(), this->stored[i - 1]->pointsOfContact[this->stored[i].get()]);
			g.setColor(0xFF, 0x00, 0xFF, 0xFF);
			g.drawLine(MegaBase::renderer, *MegaBase::offset);
			
			Line pe(this->stored[i]->structure.getCenter(), this->stored[i]->pointsOfContact[this->stored[i - 1].get()]);
			pe.setColor(0xFF, 0xFF, 0xFF, 0xFF);
			pe.drawLine(MegaBase::renderer, *MegaBase::offset);
		}
	}
	for (SectorPtr& sec: this->stored) {
		sec->structure.setColorChannels(0xFF, 0x00, 0x00, 0xFF);
		sec->draw();
	}
}
