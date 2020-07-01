#pragma once
#ifndef GAME_INSTANCE_H
#define GAME_INSTANCE_H
#include "game_entities/base/ThingBase.h"
#include "game_entities/CollisionHandler.h"
#include "game_entities/SectorGroup.h"
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
		friend class SectorGroup; // TODO: Make this not sloppy
		Point offset;
		Rect playableArea;
		SDL_Renderer* renderer;
		std::shared_ptr<ThingBase> PLAYER;
		std::vector<ThingPtr> allThings;
		std::vector<ThingPtr> drawThings;
		std::vector<ThingPtr> collisionThings;
		
		std::vector<ThingPtr> shortTermMemory; // Projectiles and such that might collide but can be removed with less overhead
		
		std::vector<ThingPtr> movingThings; // List of everything thats position can change
		std::set<ThingBase*, compare> drawOrder;
	public:
		CollisionHandler collision;
		SectorGroup sectors;
		std::map<std::string, int> gameState;
	
		GameInstance(SDL_Renderer* renderer, BoundedPoint offset);
		~GameInstance();
		Point& getOffset();
		Rect getPlayableArea() const;
		SDL_Renderer* getRenderer();
		void addThing(const ThingPtr& thing);
		void addPlayer(const ThingPtr& thing);
		void instanceBegin();
		void update();
		void draw();
		std::shared_ptr<ThingBase> getPlayer();
		
		template<typename T, typename... Args> void createThing(Args... args) {
			static_assert(std::is_base_of<ThingBase, T>::value, "createThing must be templated with a class that derives from ThingBase.");
			this->addThing(std::make_shared<T>(args...));
		}
};

#endif
