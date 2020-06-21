#include "SectorPath.h"
#include<map>
#include<algorithm>

typedef std::shared_ptr<Sector> SectorPtr;

struct VALUE {
	double value = 10000000;
};

double getValue(SectorPtr sector, SectorPtr target) {
	return sector->structure.getCenter().fastDistanceToPoint(target->structure.getCenter());
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
		if (getValue(current, target) < NODE::NODE_DISTANCE_MAX) {
			std::vector<SectorPtr> temp;
			std::map<SectorPtr, SectorPtr>::iterator it = path.find(current);
			while (it != path.end()) {
				temp.push_back(it->first);
				it = path.find(it->second);
			}
			std::vector<SectorPtr>::reverse_iterator iter = temp.rbegin();
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
			double general = cost[current].value + current->getDistance(node);
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
	return this->stored.size() == this->index;
}

int SectorPath::size() {
	return this->stored.size();
}

Point SectorPath::currentTarget(Point currentPosition) {
	if (!this->index) return Point();
	if (this->index == 0) {
		if (!this->stage) {
			if (currentPosition.distanceToPoint(this->stored[index]->structure.getCenter()) < 2.5) this->stage = true;
			return (this->stored[index]->structure.getCenter() - currentPosition).getUnitVector();
		}
		return (this->stored[index]->pointsOfContact[this->stored[index + 1].get()] - currentPosition).getUnitVector();
	}
	return Point(rand(), rand());
}

void SectorPath::clear() {
	this->stored.clear();
}

void SectorPath::draw(Point point) {
	for (const SectorPtr& sec) sec->draw();
}
