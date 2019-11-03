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
		PathManager(EnemyBase* target = NULL);
		~PathManager();
		void addPath(Path* path);
		void removePath(int index);
		void setRepeat(bool val);
		void update();
		void pause();
		void unpause();
};
