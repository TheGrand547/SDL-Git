#pragma once
#ifndef ENEMY_DRAW_GROUP_H
#define ENEMY_DRAW_GROUP_H
#include<vector>
#include "DrawGroup.h"
#include "base/EnemyBase.h"
class EnemyDrawGroup : public DrawGroup {
	private:
		std::vector<EnemyBase*> vector;
	public:
		EnemyDrawGroup();
		~EnemyDrawGroup();
		void add(EnemyBase* entity);
		void update();
		void drawGroup();
};
#endif
