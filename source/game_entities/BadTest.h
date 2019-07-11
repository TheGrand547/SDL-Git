#pragma once
#include<SDL2/SDL.h>
#include<cmath>
#include<math.h>
#include "base/EnemyBase.h"
#include "../wrappers/Texture.h"
#include "../wrappers/Timer.h"
#include "paths/CirclePath.h"
#include "paths/PathManager.h"
#include "paths/LinePath.h"
#include "../primitives/Point.h"
#include "CollideBaseGroup.h"
#include "../primitives/Line.h"
#include "../essential/random.h"

class BadTest : public EnemyBase {
	private:
		PathManager<EnemyBase>* c; // <- Figure out why this is a pointer
		// TEMP FOR AI TESTING
		bool running = true;
		Node* stored = NULL;
	public:
		BadTest(Point position);
		BadTest(const BadTest& that);
		~BadTest();
		bool checkLocationValidity() override;
		Point getPos();
		void render(Dot* dot) override;
		void set();
		void update() override;
};
