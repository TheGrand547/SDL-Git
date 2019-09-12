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
#include "base/EnemyBase.h"
#include "paths/CirclePath.h"
#include "paths/LinePath.h"
#include "paths/PathManager.h"
#include "NodePath.h"

class BadTest : public EnemyBase {
	private:
		PathManager<EnemyBase> c{this};
	public:
		BadTest(EnemyDrawGroup* parent, Point position);
		BadTest(const BadTest& that);
		~BadTest();
		bool isLocationInvalid() override;
		Point getPos() override;
		Point getCenter() override;
		void draw(SDL_Renderer* renderer, BoundedPoint& offset) override;
		void setTexture();
		void update() override;
};
