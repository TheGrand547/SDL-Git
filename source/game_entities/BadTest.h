#pragma once
#ifndef BAD_TEST_H
#define BAD_TEST_H
#include "../primitives/Line.h"
#include "../primitives/Point.h"
#include "../primitives/Polygon.h"
#include "base/EnemyBase.h"
#include "paths/PathManager.h"

class BadTest : public EnemyBase {
	private:
		PathManager c{this};
		// Quick and dirty mockup of the finite-state machine AI
		enum State {
			PATROL, GOTO, ENGAGE, RETURN, ERROR, STANDBY
		};
		State currentState;
		Point lastPatrolledPoint, targetPoint;
	public:
		BadTest(Point position);
		~BadTest();
		bool doesLineCollide(const Line& ray) const override;
		bool overlap(const Polygon& other) const override;
		bool overlap(const std::shared_ptr<ThingBase>& other) const override;
		bool isLocationInvalid() const override;
		double originDistance() const override;
		Point collideLine(const Line& ray) const override;
		Point getPosition() const override;
		Point getCenter() const override;
		Rect getBoundingRect() const override;
		void draw() override;
		void setTexture();
		void update() override;
};
#endif
