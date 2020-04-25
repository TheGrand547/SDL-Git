#pragma once
#ifndef GAME_INSTANCE_H
#define GAME_INSTANCE_H
#include "essential/log.h"
#include "AlertTextHandler.h"
#include "game_entities/base/ThingBase.h"
#include "game_entities/CollisionHandler.h"
#include "game_entities/NodeDrawGroup.h"
#include<map>
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
		Rect playableArea;
		SDL_Renderer* renderer;
		
		std::vector<std::shared_ptr<ThingBase>> allThings;
		std::vector<std::shared_ptr<ThingBase>> drawThings;
		std::vector<std::shared_ptr<ThingBase>> collisionThings;
		
		std::vector<std::shared_ptr<ThingBase>> movingThings; // List of everything that's position won't change
		std::set<ThingBase*, compare> drawOrder;
	public:
		CollisionHandler collision;
		NodeDrawGroup nodes{this};
		std::map<std::string, int> gameState;
	
		GameInstance(SDL_Renderer* renderer, BoundedPoint offset);
		~GameInstance();
		Point& getOffset();
		Rect getPlayableArea() const;
		SDL_Renderer* getRenderer();
		void addThing(std::shared_ptr<ThingBase> thing);
		void addNode(Point position, std::string data = "");
		void instanceBegin();
		void update();
		void draw();
		
		template<typename T, typename... Args> void createThing(Args... args) {
			this->addThing(std::make_shared<T>(args...));
		}
};

#endif
