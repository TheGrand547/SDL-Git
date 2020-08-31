#pragma once
#ifndef GAME_INSTANCE_H
#define GAME_INSTANCE_H
#include "game_entities/base/ThingBase.h"
#include "game_entities/BackgroundGroup.h"
#include "game_entities/CollisionHandler.h"
#include "game_entities/SectorGroup.h"
#include "essential/log.h"
#include "primitives/Rect.h"
#include "primitives/Polygon.h"
#include "TextHandler.h"
#include "BoundedPoint.h"
#include<map>
#include<memory>
#include<set>
#include<vector>

class Dot;

typedef uint32_t Uint32;
typedef uint8_t Uint8;
typedef std::shared_ptr<ThingBase> ThingPtr;

struct compare {
	bool operator()(const ThingBase* lhs, const ThingBase* rhs) const;
};

class GameInstance {
	protected:
		friend class CollisionHandler;
		friend class SectorGroup;
		friend class Dot;
		bool started;
		
		Point offset;
		Rect playableArea;
		SDL_Renderer* renderer;
		SDL_Window* window;
		std::shared_ptr<ThingBase> PLAYER;
		std::vector<ThingPtr> allThings;
		std::vector<ThingPtr> drawThings;
		std::vector<ThingPtr> collisionThings;
		
		std::vector<ThingPtr> updateThings;
				
		std::vector<ThingPtr> movingThings; // List of everything thats position can change
		std::set<ThingBase*, compare> drawOrder;
		Timer frameTimer;
		
	public:
		BackgroundGroup ground;
		CollisionHandler collision;
		SectorGroup sectors;
		std::map<std::string, int> gameState;
	
		GameInstance(SDL_Window* window, SDL_Renderer* renderer, BoundedPoint offset);
		~GameInstance();
		void addThing(const ThingPtr& thing);
		void removeThing(const ThingPtr& thing);
		Point& getOffset();
		Rect getPlayableArea() const;
		SDL_Renderer* getRenderer();
		void addPlayer(const ThingPtr& thing);
		void draw();
		void finalizeFrame();
		void instanceBegin();
		void update();
		std::shared_ptr<ThingBase> getPlayer();
		
		template<typename T, typename... Args> std::shared_ptr<T> createThing(Args... args) {
			static_assert(std::is_base_of<ThingBase, T>::value, "createThing must be templated with a class that derives from ThingBase.");
			std::shared_ptr<T> value = std::make_shared<T>(args...);
			this->addThing(value);
			return value;
		}
};

#endif
