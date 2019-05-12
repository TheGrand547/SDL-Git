#pragma once
#include<SDL2/SDL.h>
#include<math.h>
#include "base/EnemyBase.h"
#include "../wrappers/Texture.h"
#include "../wrappers/Timer.h"
#include "paths/CirclePath.h"
#include "paths/PathManager.h"
#include "paths/LinePath.h"
#include "../primatives/Point.h"

class BadTest : public EnemyBase {
	public:
		// Feels wrong to have a public member for some reason <- Maybe change this later
		PathManager<EnemyBase>* c;
		
		BadTest(Point position, std::vector<Box*>* collide) : EnemyBase(collide, position) {
			this->c = new PathManager<EnemyBase>(this);
			
			this->c->AddPath(new LinePath<EnemyBase>(Point(200, -200), toTicks(1)));
			this->c->AddPath(new CirclePath<EnemyBase>(40, 1, Path<Point>::SINGLE_LOOP, false));
			this->c->AddPath(new LinePath<EnemyBase>(Point(-200, 200), toTicks(1)));
			this->c->AddPath(new CirclePath<EnemyBase>(40, 1, Path<Point>::SINGLE_LOOP, false));			
			this->c->setRepeat(true);
		}
		
		~BadTest() {
			delete this->c;
		}
		
		void update() {
			this->c->update();
		}
		
		void set(SDL_Renderer* renderer) {
			this->texture->createBlank(renderer, 50, 50, 0xFF0000FF);
		}
		
		Point getPos() {
			return Point(*this->position);
		}
};
