#pragma once
#include "Path.h"
#include<vector>

template<class T>
class PathManager {
	protected:
		std::vector<Path<T>*>* paths;
	public:
		PathManager() {
			this->paths = new std::vector<Path<T>*>;
		}
		
		~PathManager() {
			
			typename std::vector<Path<T>*>::iterator it = this->paths->begin();
			while (it != this->paths->end()) {
				delete this->paths->front();
				it = this->paths->erase(it);
			}
			paths->clear();
			delete paths;
		}
		
		void AddPath(Path<T>* path) {
			this->paths->push_back(path);
		}
		
		void update() {
			if (paths->size() > 0) {
				if ((*paths)[0]->isFinished()) {
					delete this->paths->front();
					this->paths->erase(this->paths->begin());
					(*paths)[0]->start();
				}
				(*paths)[0]->update();
			}
		}	
};
