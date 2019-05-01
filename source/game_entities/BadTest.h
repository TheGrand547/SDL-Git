#pragma once
#include<SDL2/SDL.h>
#include<math.h>
#include "base/EnemyBase.h"
#include "../wrappers/Texture.h"
#include "../wrappers/Timer.h"
#include "paths/CirclePath.h"

class BadTest : public EnemyBase {
	protected:
		int* count;
		CirclePath* c;
	public:
		BadTest(Point position) : EnemyBase(position) {
			this->count = new int(0);
			this->c = new CirclePath(this->position, 50, .1);
			this->c->start();
		}
		
		~BadTest() {
			delete this->count;
		}
		
		void update() {
			*this->count += 1;
			/* TODO: Create a class for creating paths */
			//*this->position += Point(10*cos(*this->count), 10*sin(*this->count));
			this->c->update();
			//std::cout << *this->position;
			
		}
		
		void set(SDL_Renderer* renderer) {
			this->texture->createBlank(renderer, 50, 50, 0xFF0000FF);
		}
};
