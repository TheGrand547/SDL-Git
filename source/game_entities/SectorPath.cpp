#include "SectorPath.h"
#include "../GameInstance.h"
#include "../essential/MegaBase.h"
#include<map>
#include<algorithm>

typedef std::shared_ptr<SectorBase> SectorPtr;

struct VALUE {
	double value = 10000000;
};

double getValue(SectorPtr sector, SectorPtr target) {
	return sector->structure().getCenter().fastDistanceToPoint(target->structure().getCenter()) * ((sector->contains(target.get()) ? .25 : 1));
}

double edgeFunction(SectorPtr sector, SectorPtr target) {
	return sector->pointsOfContact()[target.get()].fastDistanceToPoint(target->structure().getCenter());
}

SectorPath::SectorPath() : stage(false), index(0) {}

SectorPath::SectorPath(SectorPtr startingSector, SectorPtr target) {
	this->getPath(startingSector, target);
}

SectorPath::~SectorPath() {
	this->clear();
}

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
	return this->stored.size() == (uint)this->index + 1;
}

int SectorPath::size() {
	return this->stored.size();
}

Point SectorPath::currentTarget(Point currentPosition) {
	if (!this->stored.size() || (int)this->stored.size() <= this->index) return Point();
	if (this->index + 1 == (int)this->stored.size()) {
		if ((this->stored[this->index]->structure().getCenter() - currentPosition).getFastMagnitude() < 5) {
			this->index++; 
			return Point();
		}
		return (this->stored[this->index]->structure().getCenter() - currentPosition).getUnitVector();
	}
	if ((this->stored[index]->pointsOfContact()[this->stored[index + 1].get()] - currentPosition).getFastMagnitude() < 5) {
		this->index++;
		this->stage = false;
	}
	if (!this->stage && this->index != 0) {
		if (currentPosition.distanceToPoint(this->stored[this->index]->structure().getCenter()) < 2.5) this->stage = true;
		return (this->stored[this->index]->structure().getCenter() - currentPosition).getUnitVector();
	}
	return (this->stored[this->index]->pointsOfContact()[this->stored[this->index + 1].get()] - currentPosition).getUnitVector();
}

Point SectorPath::currentTargetV2(Point currentPosition) {
	switch (this->stored.size()) {
		case 1: 
			if ((this->stored[0]->structure().getCenter() - currentPosition).getFastMagnitude() > 10) {
				return (this->stored[0]->structure().getCenter() - currentPosition).getUnitVector();
			}
		case 0: return Point();
		default:
			if ((this->stored[0]->pointsOfContact()[this->stored[1].get()] - currentPosition).getFastMagnitude() < 10) this->stored.erase(this->stored.begin());
			if (this->parent->collision.doesCollideWith(Line(currentPosition, this->stored[0]->pointsOfContact()[this->stored[1].get()]))) {
				return (this->stored[this->index]->structure().getCenter() - currentPosition).getUnitVector();
			}
			return (this->stored[0]->pointsOfContact()[this->stored[1].get()] - currentPosition).getUnitVector();
	}
}

void SectorPath::clear() {
	this->index = 0;
	this->stage = false;
	this->stored.clear();
}

void SectorPath::draw() {
	for (uint i = this->index; i + 1 < this->stored.size(); i++) {
		Line p(this->stored[i]->structure().getCenter(), this->stored[i]->pointsOfContact()[this->stored[i + 1].get()]);
		p.setColor(0xFF, 0x00, 0xFF, 0xFF);
		p.drawLine(MegaBase::renderer, *MegaBase::offset);
		if (i != 0) {
			Line g(this->stored[i]->structure().getCenter(), this->stored[i - 1]->pointsOfContact()[this->stored[i].get()]);
			g.setColor(0xFF, 0x00, 0xFF, 0xFF);
			g.drawLine(MegaBase::renderer, *MegaBase::offset);
			
			Line pe(this->stored[i]->structure().getCenter(), this->stored[i]->pointsOfContact()[this->stored[i - 1].get()]);
			pe.setColor(0xFF, 0xFF, 0xFF, 0xFF);
			pe.drawLine(MegaBase::renderer, *MegaBase::offset);
		}
	}
	for (SectorPtr& sec: this->stored) {
		sec->structure().setColorChannels(0xFF, 0x00, 0x00, 0xFF);
		sec->draw();
	}
}

void SectorPath::getPath(SectorPtr startingSector, SectorPtr target) {
	this->clear();
	if (startingSector.get() == target.get()) return;
	if (startingSector->contains(target.get())) {
		this->stored = {startingSector, target};
		return;
	}
	
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
		for (std::weak_ptr<SectorBase> weak: current->attached()) {
			SectorPtr node = weak.lock();
			if (!node) continue;
			double general = cost[current].value + edgeFunction(node, current);
			if (general < cost[node].value) {
				path[node] = current;
				cost[node].value = general;
				currentCost[node].value = cost[node].value + getValue(node, target);
				if (valueNotInVector(unused, node)) unused.push_back(node);
			}
		}
	}
}
