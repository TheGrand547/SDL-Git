#pragma once
#include<SDL2/SDL.h>
#include "../essential/constants.h">
#include "../wrappers/Texture.h"


class EnemyBase {
	private:
		Texture* texture;
		Point* position;
	public:
		EnemyBase(Point position) {
			this->position = new Point(position);
		}
		
		~EnemyBase() {
			delete this->position;
		}
		
		virtual void update() = 0;
		
		void render(SDL_Renderer* renderer, Point offset) {
			this->texture->setPos(this->position);
			this->texture->render(renderer, offset);
		}
};
