#pragma once
#include "../base/EnemyBase.h"
#include "Path.h"
#include<vector>
#include<memory>

typedef uint Uint;

class PathManager {
	protected:
		std::vector<std::shared_ptr<Path>> paths;
		EnemyBase* target;
		bool repeat;
		Uint index;
	public:
		PathManager(EnemyBase* target = NULL);
		~PathManager();
		bool paused();
		void addPath(std::shared_ptr<Path> path);
		void removePath(int index);
		void setRepeat(bool val);
		void update();
		void pause();
		void unpause();
};
