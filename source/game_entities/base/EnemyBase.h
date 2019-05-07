#pragma once
#include<SDL2/SDL.h>
#include "../../essential/constants.h">
#include "../../wrappers/Texture.h"


class EnemyBase {
	protected:
		Texture* texture;
		Point* position;
	public:
	
		EnemyBase(Point position = Point(0, 0)) {
			this->position = new Point(position);
			this->texture = new Texture();
		}
		
		~EnemyBase() {
			delete this->position;
		}
		
		virtual void update() = 0;
		
		void render(SDL_Renderer* renderer, Point offset) {
			if (this->texture->isLoaded()) {
				this->update();
				this->texture->setPos(this->position);
				this->texture->render(renderer, offset);
			}
		}
};
