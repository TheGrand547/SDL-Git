#pragma once
#ifndef GAME_INSTANCE_H
#define GAME_INSTANCE_H

class GameInstance;
class _CollisionHandler;

#include "essential/log.h"
#include "essential/SDL_Headers.h"
#include "game_entities/base/ThingBase.h"
#include "game_entities/BackgroundGroup.h"
#include "game_entities/SectorGroup.h"
#include "primitives/Polygon.h"
#include "primitives/Rect.h"
#include "wrappers/Timer.h"
#include "BoundedPoint.h"
#include "TextHandler.h"
#include <map>
#include <memory>
#include <queue>
#include <set>
#include <vector>

typedef std::shared_ptr<ThingBase> ThingPtr;
typedef std::vector<ThingPtr> ThingVector;
typedef std::queue<ThingPtr> ThingQueue;

class GameInstance {
	protected:
		friend class CollisionHandler;
		friend class SectorGroup;
		friend class Dot;

		bool iterating, started;

		Renderer renderer;
		Rect playableArea;

		SDL_Window* window;
		std::shared_ptr<ThingBase> PLAYER;

		TextHandler text;
		Timer frameTimer;

		ThingQueue delayed;
		ThingQueue remove;

		ThingVector allThings;
		ThingVector drawThings;
		ThingVector collisionThings;
		ThingVector updateThings;
		ThingVector movingThings; // List of everything that can change position

		void removeThing(const ThingPtr& thing);
	public:
		BackgroundGroup ground;
		SectorGroup sectors;
		std::map<std::string, int> gameState;
		std::map<std::string, Point> gamePoints;

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

		template<typename T, typename... Args> std::shared_ptr<T> createThing(Args&&... args);
		template<typename T, typename... Args> std::shared_ptr<T> createText(Args&&... args);
};

template<typename T, typename... Args> std::shared_ptr<T> GameInstance::createThing(Args&&... args) {
	static_assert(std::is_base_of<ThingBase, T>::value, "createThing must be templated with a class that derives from ThingBase.");
	std::shared_ptr<T> value = std::make_shared<T>(std::forward<Args>(args)...);
	if (value) {
		this->addThing(value);
	} else {
		LOG("Failed to create 'Thing'");
	}
	return value;
}

template<typename T, typename... Args> std::shared_ptr<T> GameInstance::createText(Args&&... args) {
	static_assert(std::is_base_of<Text, T>::value, "createText must be templated with a class that derives from Text.");
	return this->text.createText<T>(std::forward<Args>(args)...);
}
#endif
