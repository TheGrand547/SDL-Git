#pragma once
#include<SDL2/SDL.h>
#include<cmath>
#include<math.h>
#include "../essential/random.h"
#include "../primitives/Line.h"
#include "../primitives/Point.h"
#include "../wrappers/Texture.h"
#include "../wrappers/Timer.h"
#include "CollideBaseGroup.h"
#include "NodePath.h"
#include "base/EnemyBase.h"
#include "paths/CirclePath.h"
#include "paths/LinePath.h"
#include "paths/PathManager.h"

class BadTest : public EnemyBase {
	private:
		PathManager c{this};
	public:
		BadTest(EnemyDrawGroup* parent, Point position);
		BadTest(const BadTest& that);
		~BadTest();
		bool isLocationInvalid() override;
		Point getPos() override;
		Point getCenter() override;
		void draw(SDL_Renderer* renderer, BoundedPoint& offset) override;
		void setTexture(SDL_Renderer* renderer);
		void update() override;
};
