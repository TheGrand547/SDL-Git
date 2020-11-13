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
	template<typename T> struct Node {
		T value;
		bool contains(const Node<T>& t) {
			return ((std::size_t)&t) % 3; 
		}
	};

	template<typename T> std::vector<T> generatePath(const Node<T>& start, const Node<T>& end, double(*heuristic)(const T&, const T&), 
													double(*edgeHeuristic)(const T&, const T&)) {
		using TVector = std::vector<Node<T>>;
		// A* implementation
		TVector result;
		if (start == end) {
			result = {start};
		} else if (start->contains(end)) {
			result = {start, end};
		} else {
			TVector unused = {start};
			std::map<T*, T*> path;
			path[start] = NULL;
	
			std::map<T*, VALUE> cost;
			cost[start].value = 0;
	
			std::map<T*, VALUE> currentCost;
			currentCost[&start].value = h(start.data, end.data);
	
			while (unused.size() > 0) {
				typename TVector::iterator index = unused.begin();
				for (std::size_t i = 0; i < unused.size(); i++) {
					if (currentCost[unused.begin()[i]].value < currentCost[*index].value) {
						index = unused.begin() + i;
					}
				}
				if (*index == end) {
					TVector temp;
					typename std::map<T*, T*>::iterator it = path.find(*index);
					while (it != path.end()) {
						temp.push_back(it->first);
						it = path.find(it->second);
					}
					typename TVector::reverse_iterator iter = temp.rbegin();
					for (; iter != temp.rend(); iter++) {
						result.push_back(iter[0]);
					}
					break;
				}
				Node<T>* current = *index;
				unused.erase(index);
				for (auto& weak: current->attached()) {
					Node<T>* node = weak;
					if (!node) continue;
					double general = cost[current].value + edgeFunction(node, current);
					if (general < cost[node].value) {
						path[node] = current;
						cost[node].value = general;
						currentCost[node].value = general + getValue(node, end);
						if (valueNotInVector(unused, node)) unused.push_back(node);
					}
				}
			}
		}
		return result;
	}
}

#endif;
