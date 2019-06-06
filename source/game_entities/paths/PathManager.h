#pragma once
#include<iostream>
#include "Path.h"
#include<vector>

template<class T>
class PathManager {
	protected:
		// Don't think this needs to be a pointer
		std::vector<Path<T>*>* paths;
		T* target;
		bool repeat;
		int index;
	public:
		PathManager(T* target = NULL) {
			this->paths = new std::vector<Path<T>*>;
			this->target = target;
			this->index = 0;
			this->repeat = false;
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
			this->paths->back()->setTarget(this->target);
		}
		
		void setRepeat(bool val) {
			this->repeat = val;
		}
		
		void update() {
			if (this->index < this->paths->size()) {
				if ((*paths)[this->index]->isFinished()) {
					(*paths)[this->index]->stop();
					this->index++;
					if (this->index >= this->paths->size() && this->repeat) {
						this->index = 0;
					}	
					(*paths)[this->index]->start();
				}
				(*paths)[this->index]->update();
			} 
		}	
};
