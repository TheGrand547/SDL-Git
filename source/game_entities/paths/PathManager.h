#pragma once
#include "../base/EnemyBase.h"
#include "Path.h"
#include<vector>
#include<memory>

class PathManager {
	protected:
		std::vector<std::shared_ptr<Path>> paths;
		EnemyBase* target;
		bool repeat;
		int index;
	public:
		PathManager(EnemyBase* target = NULL) {
			this->target = target;
			this->index = 0;
			this->repeat = false;
		}
		
		~PathManager() {
			paths.clear();
		}
		
		void addPath(Path* path) {
			path->setTarget(this->target);
			this->paths.push_back(std::shared_ptr<Path>(path));
		}
		
		void removePath(int index) {
			if (index < this->paths.size()) {
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
