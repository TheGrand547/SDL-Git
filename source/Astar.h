#pragma once
#ifndef A_STAR_IMPLEMENTATION_H
#define A_STAR_IMPLEMENTATION_H
#include <float.h>
#include <map>
#include <vector>

struct VALUE {
	double value = DBL_MAX;
};

namespace AStar {
	template<class T> std::vector<T> generatePath(const T& start, const T& end, double(*heuristic)(const T&, const T&)) {
		// A* implementation
		this->clear();
		std::vector<T> vector;
		if (startingSector.get() == target.get()) return;
		if (startingSector->contains(target.get())) {
			this->stored = {startingSector, target};
			return;
		}
		SectorVector unused = {startingSector};
		std::map<SectorPtr, SectorPtr> path;
		path[startingSector] = NULL;

		std::map<SectorPtr, VALUE> cost;
		cost[startingSector].value = 0;

		std::map<SectorPtr, VALUE> currentCost;
		currentCost[startingSector].value = getValue(startingSector, target);

		while (unused.size() > 0) {
			SectorVector::iterator index = unused.begin();
			for (std::size_t i = 0; i < unused.size(); i++) {
				if (currentCost[unused.begin()[i]].value < currentCost[*index].value) {
					index = unused.begin() + i;
				}
			}
			if (*index == target) {
				SectorVector temp;
				std::map<SectorPtr, SectorPtr>::iterator it = path.find(*index);
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
			SectorPtr current = *index;
			unused.erase(index);
			for (std::weak_ptr<SectorBase> weak: current->attached()) {
				SectorPtr node = weak.lock();
				if (!node) continue;
				double general = cost[current].value + edgeFunction(node, current);
				if (general < cost[node].value) {
					path[node] = current;
					cost[node].value = general;
					currentCost[node].value = general + getValue(node, target);
					if (valueNotInVector(unused, node)) unused.push_back(node);
				}
			}
		}
	}
}

#endif;
