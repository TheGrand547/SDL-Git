#pragma once
#ifndef A_STAR_IMPLEMENTATION_H
#define A_STAR_IMPLEMENTATION_H
#include <float.h>
#include <map>
#include <vector>

namespace AStar {
	struct VALUE {
		double value = DBL_MAX;
	};
	template<typename T> struct Node {
		virtual ~Node() {}
		//virtual T value() = 0;
		virtual T representation() = 0;
		virtual bool contains(Node<T>* node) const = 0;
		//virtual bool canSee(const Node<T>& node);
	};
	/*
	template<typename T> struct TrivialNode : public Node<T> {
		
	}*/

	template<typename T, typename H> std::vector<T> generatePath(const Node<T>& start, const Node<T>& end, H heuristic, 
													H edgeHeuristic) {
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
					double general = cost[current].value + edgeHeuristic(node, current);
					if (general < cost[node].value) {
						path[node] = current;
						cost[node].value = general;
						currentCost[node].value = general + heuristic(node, end);
						if (valueNotInVector(unused, node)) unused.push_back(node);
					}
				}
			}
		}
		return result;
	}
}
#endif
