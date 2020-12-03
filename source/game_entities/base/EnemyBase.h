#pragma once
#ifndef ENEMY_BASE_H
#define ENEMY_BASE_H
#include "../../wrappers/MovementWrapper.h"
#include "../../wrappers/Texture.h"
#include "../../wrappers/Timer.h"
#include "ThingBase.h"
#include <memory>
#include <vector>

class EnemyBase : public ThingBase {
	protected:
		Texture texture;
		Timer pathTimer, timer;
		int width = 50;
		int height = 50;
		double maxVelocity;
		bool turning = false;
		MovementWrapper movement;
	public:
		EnemyBase(Point position = Point(0, 0), int flags = 0);
		virtual ~EnemyBase();
		virtual bool isLocationInvalid() const = 0;
		virtual Point getCenter() const = 0;
		virtual void update() = 0;
		virtual void draw();
		virtual void move(Point velocity);
		void turn(double delta);
		void toggleTurn();
		Point pathFindTo(Point pos = Point());
};
#endif
