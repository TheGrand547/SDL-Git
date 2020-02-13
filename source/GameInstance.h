#pragma once
#ifndef GAME_INSTANCE_H
#define GAME_INSTANCE_H
#include "AlertTextHandler.h"
#include "game_entities/base/ThingBase.h"
#include "game_entities/CollisionHandler.h"
#include "game_entities/NodeDrawGroup.h"
#include<memory>
#include<set>
#include<vector>

typedef uint32_t Uint32;

struct compare {
	bool operator()(const ThingBase* lhs, const ThingBase* rhs) const;
};

class GameInstance {
	private:
		friend class CollisionHandler;
		Point offset;
		SDL_Renderer* renderer;
		
		std::vector<std::shared_ptr<ThingBase>> allThings;
		std::vector<std::shared_ptr<ThingBase>> drawThings;
		std::vector<std::shared_ptr<ThingBase>> collisionThings;
		
		std::vector<std::shared_ptr<ThingBase>> movingThings; // List of everything that's position won't change
		std::set<ThingBase*, compare> drawOrder;
	public:
		CollisionHandler collision;
		NodeDrawGroup nodes{this};
	
		GameInstance(SDL_Renderer* renderer, BoundedPoint offset);
		~GameInstance();
		Point& getOffset();
		SDL_Renderer* getRenderer();
		void addThing(std::shared_ptr<ThingBase> thing);
		void addNode(Point position, std::string data = "", bool full = true);
		void instanceBegin();
		void update();
		void draw();
};

#endif
