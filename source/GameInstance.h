#pragma once
#ifndef GAME_INSTANCE_H
#define GAME_INSTANCE_H

class GameInstance;

#include "essential/log.h"
#include "essential/SDL_Headers.h"
#include "game_entities/base/ThingBase.h"
#include "game_entities/BackgroundGroup.h"
#include "game_entities/CollisionHandler.h"
#include "game_entities/SectorGroup.h"
#include "primitives/Rect.h"
#include "primitives/Polygon.h"
#include "TextHandler.h"
#include "BoundedPoint.h"
#include<map>
#include<memory>
#include<set>
#include<vector>

typedef uint32_t Uint32;
typedef uint8_t Uint8;
typedef std::shared_ptr<ThingBase> ThingPtr;

namespace Draw {
	struct compare {
		bool operator()(const ThingBase* lhs, const ThingBase* rhs) const;
	};
}

class GameInstance {
	protected:
		friend class CollisionHandler;
		friend class SectorGroup;
		friend class Dot;
		bool started;
		
		Renderer renderer;
		Rect playableArea;
		SDL_Window* window;
		std::shared_ptr<ThingBase> PLAYER;
		std::vector<ThingPtr> allThings;
		std::vector<ThingPtr> drawThings;
		std::vector<ThingPtr> collisionThings;
		
		std::vector<ThingPtr> updateThings;
				
		std::vector<ThingPtr> movingThings; // List of everything thats position can change
		std::set<ThingBase*, Draw::compare> drawOrder;
		Timer frameTimer;
		
		std::vector<ThingPtr> remove;
		void removeThing(const ThingPtr& thing);
	public:
		BackgroundGroup ground;
		CollisionHandler collision;
		SectorGroup sectors;
		std::map<std::string, int> gameState;
	
		GameInstance(SDL_Window* window, SDL_Renderer* renderer, BoundedPoint offset);
		~GameInstance();
		Point& getOffset();
		Rect getPlayableArea() const;
		Renderer& getRenderer();
		SDL_Renderer* getTrueRenderer();
		std::shared_ptr<ThingBase> getPlayer();
		void addThing(const ThingPtr& thing);
		void addPlayer(const ThingPtr& thing);
		void draw();
		void finalizeFrame();
		void instanceBegin();
		void queueRemoval(const ThingPtr& thing);
		void update();
		
		template<typename T, typename... Args> std::shared_ptr<T> createThing(Args... args) {
			static_assert(std::is_base_of<ThingBase, T>::value, "createThing must be templated with a class that derives from ThingBase.");
			std::shared_ptr<T> value = std::make_shared<T>(args...);
			this->addThing(value);
			return value;
		}
};

#endif
