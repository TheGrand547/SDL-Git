#pragma once
#include "../base/EnemyBase.h"
#include "Path.h"
#include<vector>
#include<memory>

typedef uint Uint;

class PathManager {
	protected:
		bool repeat;
		EnemyBase* target;
		std::vector<std::shared_ptr<Path>> paths;
		Uint index;
	public:
		PathManager(EnemyBase* target = NULL);
		~PathManager();
		bool paused() const;
		void addPath(std::shared_ptr<Path> path);
		void pause();
		void removePath(int index);
		void setRepeat(bool val);
		void unpause();
		void update();
};
