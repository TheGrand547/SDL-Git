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
#include "../primitives/Line.h"

class BadTest : public EnemyBase {
	public:
		PathManager<EnemyBase>* c; // <- Figure out why this is a pointer
		
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
		
		virtual void render(Dot* dot) {
			if (this->texture->isLoaded()) {
				this->texture->setPos(this->position);
				this->texture->render(MegaBase::renderer, MegaBase::offset);
			}
			// "AI"
			std::cout << this->position << std::endl;
			for (int i = -10; i < 10; i++){
				Point pTemp = Point(this->position);
				pTemp += Point(300 * cos(this->angle + (i * M_PI / 180.0)), 300 * sin(this->angle + (i * M_PI / 180.0)));
				Line temp = Line(this->position, pTemp);
				Point newTemp = dot->getRect().collideLine(temp);
				temp.setColorChannels(COLORS::CYAN);
				temp.drawLine(MegaBase::renderer, MegaBase::offset);
			}
			
			//temp.drawLine(MegaBase::renderer, MegaBase::offset);
			/*
			if (newTemp.isReal()) {
				//std::cout << "holy shit it worked" << std::endl;
				Line newTempLine = Line(this->position, newTemp);
				newTempLine.setColorChannels(COLORS::CYAN);
				newTempLine.drawLine(MegaBase::renderer, MegaBase::offset);
			}*/
		}
		
		void update() {
			if (!this->texture->isLoaded()) {
				this->set();
			}
			// Basic AI(hopefully)
			
			this->c->update();
		}
		
		Point getPos() {
			return this->position;
		}
};
