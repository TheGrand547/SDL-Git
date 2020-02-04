#pragma once
#ifndef GAME_INSTANCE_H
#define GAME_INSTANCE_H
#include "AlertTextHandler.h"
#include "CollisionHandler"
#include "game_entities/CollideBaseGroup.h" // Actually I think this is redundant and should be removed
#include "game_entities/NodeDrawGroup.h"
#include<memory>
#include<set>
#include<vector>

typedef uint32_t Uint32;

struct compare {
	bool operator()(const ThingBase* lhs, const ThingBase* rhs);
};

class GameInstance {
	private:
		friend class CollisionHandler;
		//CollideBaseGroup collision;
		//NodeDrawGroup nodes;
		BoundedPoint offset;
		SDL_Renderer* renderer;
		
		std::vector<std::shared_ptr<ThingBase>> allThings;
		std::vector<std::shared_ptr<ThingBase>> drawThings;
		std::vector<std::shared_ptr<ThingBase>> collision;
		
		std::vector<std::shared_ptr<ThingBase>> movingThings; // List of everything that's position won't change
		std::set<ThingBase*, compare> drawOrder;
	public:
		GameInstance(SDL_Renderer* renderer);
		~GameInstance();
		SDL_Renderer* getRenderer();
		void addThing(std::shared_ptr<ThingBase> thing);
		void update();
		//CollideBaseGroup& getCollision() {return this->collision;}
		//NodeDrawGroup& getNodes() {return this->nodes;}
};

#endif
