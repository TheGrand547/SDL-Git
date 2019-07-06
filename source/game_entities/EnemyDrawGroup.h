#pragma once
#ifndef ENEMY_DRAW_GROUP_H
#define ENEMY_DRAW_GROUP_H
#include<vector>
#include "DrawGroup.h"
#include "NodeDrawGroup.h"
#include "base/EnemyBase.h"
class EnemyDrawGroup : public DrawGroup {
	private:
		std::vector<EnemyBase*> vector;
		Dot* dot;
		CollideBaseGroup* collide;
		NodeDrawGroup* nav;
	public:
		EnemyDrawGroup();
		~EnemyDrawGroup();
		void add(EnemyBase* entity);
		void update();
		void drawGroup();
		void setDot(Dot* dot);
		void setCollision(CollideBaseGroup* collision);
		void setNavigation(NodeDrawGroup* nav);
};
#endif
