#pragma once
#include<SDL2/SDL.h>
#include<math.h>
#include "base/EnemyBase.h"
#include "../wrappers/Texture.h"
#include "../wrappers/Timer.h"
#include "paths/CirclePath.h"
#include "paths/PathManager.h"
#include "paths/LinePath.h"
#include "../primitives/Point.h"
#include "CollideBaseGroup.h"

class BadTest : public EnemyBase {
	public:
		// Feels wrong to have a public member for some reason <- Maybe change this later
		PathManager<EnemyBase>* c;
		
		BadTest(Point position, CollideBaseGroup* collide) : EnemyBase(collide, position) {
			this->c = new PathManager<EnemyBase>(this);
			this->c->AddPath(new LinePath<EnemyBase>(Point(200, -200), toTicks(1)));
			this->c->AddPath(new CirclePath<EnemyBase>(40, 1, Path<Point>::SINGLE_LOOP, false));
			this->c->AddPath(new LinePath<EnemyBase>(Point(-200, 200), toTicks(1)));
			this->c->AddPath(new CirclePath<EnemyBase>(40, 1, Path<Point>::SINGLE_LOOP, false));			
			this->c->setRepeat(true);
		}
		
		BadTest(const BadTest& that) : EnemyBase(that.collide, that.position) {
			*this = BadTest(that.position, that.collide);
		}
		
		~BadTest() {
			delete this->c;
		}
		
		void set() {
			this->texture->createBlank(MegaBase::renderer, 50, 50, 0xFF0000FF);
		}
		
		void update() {
			if (!this->texture->isLoaded()) {
				this->set();
			}
			this->c->update();
		}
		
		Point getPos() {
			return this->position;
		}
};
