#pragma once
#include<SDL2/SDL.h>
#include<math.h>
#include "base/EnemyBase.h"
#include "../wrappers/Texture.h"
#include "../wrappers/Timer.h"
#include "paths/CirclePath.h"
#include "paths/PathManager.h"

class BadTest : public EnemyBase {
	protected:
		int* count;
	public:
		PathManager<Point>* c;
		BadTest(Point position) : EnemyBase(position) {
			this->count = new int(0);
			this->c = new PathManager<Point>();
			this->c->AddPath(new CirclePath(this->position, 40, 1, Path<Point>::REPEAT, false));
		}
		
		~BadTest() {
			delete this->count;
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
