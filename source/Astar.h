#pragma once
#ifndef A_STAR_IMPLEMENTATION_H
#define A_STAR_IMPLEMENTATION_H
#include <float.h>
#include <map>
#include <memory>
#include <type_traits>
#include <vector>

namespace AStar {
	struct VALUE {
		double value = DBL_MAX;
	};
	template<typename T> struct Node : public std::enable_shared_from_this<Node<T>> {
		std::vector<std::weak_ptr<Node<T>>> attach;
		T t;
		Node(T& t) : t(t) {}
		~Node() {}
		std::vector<std::weak_ptr<Node<T>>>& attached() {
			return this->attach;
		}
		bool contains(std::shared_ptr<Node<T>> node) const {
			for (std::weak_ptr<Node<T>> weak : this->attach) {
				std::shared_ptr<Node<T>> locked = weak.lock();
				if (locked && node == locked) return true;
			}
			return false;
		}
	};

	template<typename T, typename H, typename G> std::vector<std::shared_ptr<T>> generatePath(const std::shared_ptr<T>& start, const std::shared_ptr<T>& end, H heuristic, G edgeHeuristic) {
		using TPtr = std::shared_ptr<T>;
		using TVector = std::vector<TPtr>;
		// A* implementation
		TVector result;
		if (start == end) {
			result = {start};
		} else if (start->contains(end)) {
			result = {start, end};
		} else {
			TVector unused = {start};
			std::map<TPtr, TPtr> path;
			std::map<TPtr, VALUE> cost;
			std::map<TPtr, VALUE> currentCost;
			path[start];
			cost[start].value = 0;
			currentCost[start].value = heuristic(start, end);
	
			while (unused.size() > 0) {
				typename TVector::iterator index = unused.begin();
				for (std::size_t i = 0; i < unused.size(); i++) {
					if (currentCost[unused.begin()[i]].value < currentCost[*index].value) {
						index = unused.begin() + i;
					}
				}
				if (*index == end) {
					TVector temp;
					typename std::map<TPtr, TPtr>::iterator it = path.find(*index);
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
				std::shared_ptr<T> current = *index;
				unused.erase(index);
				for (auto& weak: current->attached()) {
					std::shared_ptr<T> node = weak.lock();
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
	/*
	template<typename T, typename H, typename G> std::vector<T> generatePath(const T& start, const T& end, H heuristic, G edgeHeuristic) {
		static_assert(std::is_invokable<H>::value);
		static_assert(std::is_invokable<G>::value);
		using TVector = std::vector<T>;
		// A* implementation
		TVector result;
		if (start == end) {
			result = {start};
		} else if (start->contains(end)) {
			result = {start, end};
		} else {
			TVector unused = {start};
			std::map<T, T> path;
			std::map<T, VALUE> cost;
			std::map<T, VALUE> currentCost;
			path[start];
			cost[start].value = 0;
			currentCost[start].value = heuristic(start, end);
	
			while (unused.size() > 0) {
				typename TVector::iterator index = unused.begin();
				for (std::size_t i = 0; i < unused.size(); i++) {
					if (currentCost[unused.begin()[i]].value < currentCost[*index].value) {
						index = unused.begin() + i;
					}
				}
				if (*index == end) {
					TVector temp;
					typename std::map<T, T>::iterator it = path.find(*index);
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
				T current = *index;
				unused.erase(index);
				for (auto& weak: current.attached()) {
					T node = weak.lock();
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
	}*/
}
#endif
