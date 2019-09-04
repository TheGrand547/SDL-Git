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
		NodePath path;
		PathManager<EnemyBase> c{this};
		Timer pathTimer;
		
		Node* getClosestUnblockedNode();
	public:
		BadTest(Point position);
		BadTest(const BadTest& that);
		~BadTest();
		bool isLocationInvalid() override;
		Point getPos();
		Point getCenter();
		void draw(Dot* dot) override;
		void setTexture();
		void update() override;
};
