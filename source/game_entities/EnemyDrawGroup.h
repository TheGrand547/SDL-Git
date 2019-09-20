#pragma once
#ifndef ENEMY_DRAW_GROUP_H
#define ENEMY_DRAW_GROUP_H
#include<memory>
#include<vector>
#include "DrawGroup.h"
#include "NodeDrawGroup.h"
class EnemyDrawGroup;
#include "base/EnemyBase.h"

class EnemyDrawGroup : public DrawGroup {
	private:
		std::vector<std::shared_ptr<EnemyBase>> vector;
		Dot* dot;
		SDL_Renderer* renderer;
		BoundedPoint* offset;
	public:		
		EnemyDrawGroup(CollideBaseGroup& collision, NodeDrawGroup& nav, SDL_Renderer* renderer, BoundedPoint& offset);
		~EnemyDrawGroup();
		bool exists() override;
		Dot* getDot();
		int size() override;
		void clearGroup() override;
		void drawGroup() override;
		void update();
		void setDot(Dot* dot);
		void add(std::shared_ptr<EnemyBase> entity);
		
		CollideBaseGroup* collide;
		NodeDrawGroup* nav;
};
#endif
