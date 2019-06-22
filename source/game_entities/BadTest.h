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
#include "../essential/random.h"

class BadTest : public EnemyBase {
	public:
		PathManager<EnemyBase>* c; // <- Figure out why this is a pointer
		
		BadTest(Point position) : EnemyBase(position) {
			this->c = new PathManager<EnemyBase>(this);
			
			this->c->AddPath(new LinePath<EnemyBase>(Point(200, -200), toTicks(1)));
			this->c->AddPath(new CirclePath<EnemyBase>(40, 1, Path<Point>::SINGLE_LOOP, false));
			this->c->AddPath(new LinePath<EnemyBase>(Point(-200, 200), toTicks(1)));
			this->c->AddPath(new CirclePath<EnemyBase>(40, 1, Path<Point>::SINGLE_LOOP, false));			
			this->c->setRepeat(true);
		}
		
		BadTest(const BadTest& that) : EnemyBase(that.position) {
			*this = BadTest(that.position);
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
			/*
			Point center = this->position + Point() + Point(this->width / 2, this->height / 2);
			bool flag = false;
			for (int i = -20; i <= 20; i++) {
				Point pTemp = Point(center);
				pTemp += Point(300 * cos(this->angle + radians(i)), 300 * sin(this->angle + radians(i)));
				Line temp = Line(center, pTemp);
				Point newTemp = dot->getRect().collideLine(temp);
				if (newTemp.isReal()) {
					if (!flag && center.distanceToPoint(newTemp) > 50) {
						*this += Point(2 * cos(this->angle + radians(i)), 2 * sin(this->angle + radians(i)));
						flag = !flag;
					}
					Line newTempLine = Line(center, newTemp);
					newTempLine.setColorChannels(COLORS::CYAN);
					newTempLine.drawLine(MegaBase::renderer, MegaBase::offset);
					continue;
				}
				temp.setColorChannels(COLORS::BLACK);
				temp.drawLine(MegaBase::renderer, MegaBase::offset);
			}*/
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
