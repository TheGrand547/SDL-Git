#pragma once
#include<SDL2/SDL.h>
#include "../../essential/constants.h"
#include "../../wrappers/Texture.h"
#include "CollideBase.h"
#include<vector>

class EnemyBase {
	protected:
		Texture* texture;
		Point position;
		
		int width = 50;
		int height = 50;
		
		/* Experimental */
		std::vector<Box*>* collide;
	public:
		EnemyBase(std::vector<Box*>* collision, Point position = Point(0, 0)) {
			this->position = position;
			this->texture = new Texture();
			this->collide = collision;
		}
		
		virtual ~EnemyBase() {
			delete this->texture;
		}
		
		virtual void update() = 0;
		
		void render(SDL_Renderer* renderer, Point offset) {
			if (this->texture->isLoaded()) {
				this->update();
				this->texture->setPos(this->position);
				this->texture->render(renderer, offset);
			}
		}
		
		void operator+=(Point delta) {
			bool xflag = false;
			bool yflag = false;
			Point px = delta;
			for (int i = 1; i < 6; i++) {
				if (!yflag) {
					if (collideRectTest(Rect(this->position, this->width, this->height) + px.onlyX()/i, this->collide)) {
						this->position += px.onlyX()/i;
						yflag = true;
					}
				}
				if (!xflag) {
					if (collideRectTest(Rect(this->position, this->width, this->height) + px.onlyY()/i, this->collide)) {
						this->position += px.onlyY()/i;					
						xflag = true;
					}
				}
				if (xflag && yflag) {
					break;
				}
			}
		}
};
