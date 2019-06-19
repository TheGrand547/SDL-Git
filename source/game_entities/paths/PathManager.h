#pragma once
#include<iostream>
#include "Path.h"
#include<vector>

template<class T>
class PathManager {
	protected:
		std::vector<Path<T>*> paths;
		T* target;
		bool repeat;
		int index;
	public:
		PathManager(T* target = NULL) {
			this->target = target;
			this->index = 0;
			this->repeat = false;
		}
		
		~PathManager() {
			typename std::vector<Path<T>*>::iterator it = this->paths.begin();
			while (it != this->paths.end()) {
				delete this->paths.front();
				it = this->paths.erase(it);
			}
			paths.clear();
		}
		
		void AddPath(Path<T>* path) {
			this->paths.push_back(path);
			this->paths.back()->setTarget(this->target);
		}
		
		void removePath(int index) {
			if (index < this->paths.size()) {
				delete this->paths.at(index);
				this->paths.erase(this->paths.begin() + index);
			}
		}
		
		void setRepeat(bool val) {
			this->repeat = val;
		}
		
		void update() {
			if (this->index < this->paths.size()) {
				if (this->paths[this->index]->isFinished()) {
					this->paths[this->index]->stop();
					this->index++;
					if (this->index >= this->paths.size() && this->repeat) {
						this->index = 0;
					}	
					this->paths[this->index]->start();
				}
				this->paths[this->index]->update();
			} 
		}	
};
