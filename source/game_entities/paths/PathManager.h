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
			for (int i = 0; i < paths->size() - 1; i++) {
				delete (*paths)[0];
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
					paths->erase(paths->begin());
					(*paths)[0]->start();
				}
				(*paths)[0]->update();
			}
		}	
};
