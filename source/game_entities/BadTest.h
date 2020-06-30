#pragma once
#include<SDL2/SDL.h>
#include<cmath>
#include<math.h>
#include "../essential/random.h"
#include "../primitives/Line.h"
#include "../primitives/Point.h"
#include "../primitives/Polygon.h"
#include "../wrappers/Texture.h"
#include "../wrappers/Timer.h"
#include "base/EnemyBase.h"
#include "paths/CirclePath.h"
#include "paths/LinePath.h"
#include "paths/PathManager.h"
#include "paths/ZeroRadiusTurnPath.h"

class BadTest : public EnemyBase {
	private:
		PathManager c{this};
		/* Quick and dirty mockup of the finite-state machine AI */
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
		bool wideOverlap(const Polygon& other) const override;
		bool isLocationInvalid() const override;
		double originDistance() const override;
		Point collideLine(const Line& ray) const override;
		Point getPosition() const override;
		Point getCenter() const override;
		Rect getRect() const override;
		void draw(SDL_Renderer* renderer, Point offset = Point(0, 0)) override;
		void setTexture(SDL_Renderer* renderer);
		void update() override;
};
