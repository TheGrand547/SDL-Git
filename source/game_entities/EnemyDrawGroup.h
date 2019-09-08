#pragma once
#ifndef ENEMY_DRAW_GROUP_H
#define ENEMY_DRAW_GROUP_H
#include<vector>
#include "DrawGroup.h"
#include "NodeDrawGroup.h"
class EnemyDrawGroup;
#include "base/EnemyBase.h"
class EnemyDrawGroup : public DrawGroup {
	private:
		std::vector<EnemyBase*> vector;
		Dot* dot;
	public:		
		EnemyDrawGroup(CollideBaseGroup& collision, NodeDrawGroup& nav);
		~EnemyDrawGroup();
		bool exists() override;
		int size() override;
		void clearGroup() override;
		void drawGroup() override;
		void update();
		void setDot(Dot* dot);
		template<class Type, typename...Arguments> void create(Arguments... args);
		
		CollideBaseGroup* collide;
		NodeDrawGroup* nav;
};
#endif
