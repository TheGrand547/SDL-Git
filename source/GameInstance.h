#pragma once
#ifndef GAME_INSTANCE_H
#define GAME_INSTANCE_H
#include "game_entities/base/ThingBase.h"
#include "game_entities/CollisionHandler.h"
#include "essential/log.h"
#include "primitives/Rect.h"
#include "primitives/Polygon.h"
#include "AlertTextHandler.h"
#include "BoundedPoint.h"
#include<map>
#include<memory>
#include<set>
#include<vector>

typedef uint32_t Uint32;
typedef uint8_t Uint8;
typedef std::shared_ptr<ThingBase> ThingPtr;


struct compare {
	bool operator()(const ThingBase* lhs, const ThingBase* rhs) const;
};

class GameInstance {
	private:
		friend class CollisionHandler;
		Point offset;
		Rect playableArea;
		SDL_Renderer* renderer;
		std::shared_ptr<ThingBase> PLAYER;
		std::vector<std::shared_ptr<ThingBase>> allThings;
		std::vector<std::shared_ptr<ThingBase>> drawThings;
		std::vector<std::shared_ptr<ThingBase>> collisionThings;
		
		std::vector<std::shared_ptr<ThingBase>> shortTermMemory; // Projectiles and such that might collide but can be removed with less overhead
		
		std::vector<std::shared_ptr<ThingBase>> movingThings; // List of everything thats position can change
		std::set<ThingBase*, compare> drawOrder;
	public:
		CollisionHandler collision;
		std::map<std::string, int> gameState;
	
		GameInstance(SDL_Renderer* renderer, BoundedPoint offset);
		~GameInstance();
		Point& getOffset();
		Rect getPlayableArea() const;
		SDL_Renderer* getRenderer();
		void addThing(const std::shared_ptr<ThingBase>& thing);
		void addPlayer(const std::shared_ptr<ThingBase>& thing);
		void instanceBegin();
		void update();
		void draw();
		std::shared_ptr<ThingBase> getPlayer();
		
		template<typename T, typename... Args> void createThing(Args... args) {
			this->addThing(std::make_shared<T>(args...));
		}
};

#endif
