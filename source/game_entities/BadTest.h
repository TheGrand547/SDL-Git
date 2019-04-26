#pragma once
#include<SDL2/SDL.h>
#include "base/EnemyBase.h"
#include "../wrappers/Texture.h"

class BadTest : public EnemyBase {
	public:
		BadTest(Point position) : EnemyBase(position) {}
		
		void update() {}
		
		void set(SDL_Renderer* renderer) {
			this->texture->createBlank(renderer, 50, 50, 0xFF0000FF);
		}
};
