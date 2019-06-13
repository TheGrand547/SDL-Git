#pragma once
#include<SDL2/SDL.h>
#include "../../essential/constants.h"
#include "../../wrappers/Texture.h"
#include "CollideBase.h"
#include "../CollideBaseGroup.h"
#include "../../Dot.h"
#include<vector>
#include<math.h>

class EnemyBase {
	protected:
		Texture* texture;
		Point position;
		
		int width = 50;
		int height = 50;
		float angle = 0;
		
		/* Experimental */
		CollideBaseGroup* collide;
	public:
		EnemyBase(CollideBaseGroup* collision, Point position = Point(0, 0)) {
			this->position = position;
			this->texture = new Texture();
			this->collide = collision;
		}
		
		virtual ~EnemyBase() {
			delete this->texture;
			this->collide = NULL;
		}
		
		virtual void update() = 0;
		
		virtual void render(Dot* dot) {
			if (this->texture->isLoaded()) {
				this->texture->setPos(this->position);
				this->texture->render(MegaBase::renderer, MegaBase::offset);
			}
		}
		
		void operator+=(Point delta) {
			float xflag = 0;
			float yflag = 0;
			Point px = delta;
			for (int i = 1; i < 6; i++) {
				if (!xflag) {
					if (collideRectTest(Rect(this->position, this->width, this->height) + px.onlyX() / i, this->collide)) {
						xflag = px.x() / i;
					}
				}
				if (!yflag) {
					if (collideRectTest(Rect(this->position, this->width, this->height) + px.onlyY() / i, this->collide)) {
						yflag = px.y() / i;					
					}
				}
				if (xflag && yflag) {
					break;
				}
			}
			this->position += Point(xflag, yflag);
			this->angle = atan2(yflag, xflag);
		}
		
		friend std::ostream& operator<<(std::ostream &output, const EnemyBase& base) {
			output << base.position;
			return output;
		}
};
