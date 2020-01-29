#pragma once
#ifndef GAME_INSTANCE_H
#define GAME_INSTANCE_H
#include "AlertTextHandler.h"
#include "game_entities/CollideBaseGroup.h" // Actually I think this is redundant and should be removed
#include "game_entities/NodeDrawGroup.h"
#include<memory>
#include<set>
#include<vector>

typedef uint32_t Uint32;

bool compare(const ThingBase*& lhs, const ThingBase*& rhs) {
	return lhs->originDistance() < rhs->originDistance();
}

class GameInstance {
	private:
		//CollideBaseGroup collision;
		//NodeDrawGroup nodes;
		std::vector<std::shared_ptr<ThingBase>> cld;
		std::vector<std::shared_ptr<ThingBase>> drawThings;
		std::set<ThingBase*, decltype(compare)> due(decltype(compare));
	public:
		GameInstance() {}
		~GameInstance() {}
		//CollideBaseGroup& getCollision() {return this->collision;}
		//NodeDrawGroup& getNodes() {return this->nodes;}
};

#endif
