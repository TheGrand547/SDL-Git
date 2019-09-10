#pragma once
#ifndef ENEMY_DRAW_GROUP_H
#define ENEMY_DRAW_GROUP_H
#include<memory>
#include<vector>
#include "DrawGroup.h"
#include "NodeDrawGroup.h"
class EnemyDrawGroup;
#include "ai/AiBrain.h"
#include "base/EnemyBase.h"

class EnemyDrawGroup : public DrawGroup {
	private:
		std::vector<EnemyBase*> vector;
		Dot* dot;
		SDL_Renderer* renderer;
		BoundedPoint* offset;
		std::unique_ptr<AiBrain> powerslave;
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
		template<class Type, typename...Arguments> void create(Arguments... args);
		
		CollideBaseGroup* collide;
		NodeDrawGroup* nav;
};
#endif
