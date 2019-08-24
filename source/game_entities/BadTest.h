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
		Node* getClosestUnblockedNode();
		PathManager<EnemyBase> c{this};
		Timer pathTimer;
	public:
		BadTest(Point position);
		BadTest(const BadTest& that);
		~BadTest();
		bool checkLocationValidity() override;
		Point getPos();
		void draw(Dot* dot) override;
		void setTexture();
		void update() override;
};
