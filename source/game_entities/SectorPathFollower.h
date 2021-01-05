#pragma once
#ifndef SECTOR_PATH_FOLLOWER_H
#define SECTOR_PATH_FOLLOWER_H
#include "../primitives/Rect.h"
#include "../wrappers/MovementWrapper.h"
#include "../wrappers/Surface.h"
#include "../wrappers/Timer.h"
#include "base/ThingBase.h"
#include "SectorPath.h"

class SectorPathFollower : public ThingBase {
	protected:
		static inline const int VISION_WIDE = 60;
		static inline const int VISION_SHALLOW = 30;
		static inline const int VISION_RANGE = 200;
		int seen;
		bool created = false;
		MovementWrapper movement;
		Timer timer;
	public:
		// Why are these public again?
		Rect box;
		SectorPath mine;
		Surface texture;
		
		SectorPathFollower(Rect rect);
		~SectorPathFollower();
		bool doesLineCollide(const Line& ray) const override;
		bool isAlive() const override;
		bool overlap(const Polygon& other) const override;
		bool overlap(const std::shared_ptr<ThingBase>& other) const override;
		double originDistance() const override;
		Point collideLine(const Line& ray) const override;
		Point getPosition() const override;
		Rect getBoundingRect() const override;
		void draw() override;
		void update() override;
};
#endif
