#pragma once
#ifndef WANDER_AI_H
#define WANDER_AI_H
#include "Node.h"
class WanderAi {
	private:
		Node* stored;
		bool running = false;
	public:
		WanderAi() {}
		~WanderAi() {}
		void run() {
			/*
		if (this->running) {
			Point center = this->position + Point() + Point(this->width / 2, this->height / 2);
			if (this->stored == NULL) {
				std::vector<Node*> temp;
				for (int i = 0; i < this->nav->size(); i++) {
					if (checkCollisionBetweenLineAndGroup(this->collide, Line(center, (*this->nav)[i]->getPosition()))) {
						temp.push_back((*this->nav)[i]);
					}
				}
				if (temp.size() == 0) {
					// If there are no nodes with a clear line of sight then it should stop
					this->running = false;
				} else {
					// Find closest one, and select it as the current target
					Node* closest = temp[0];
					if (temp.size() > 1) {
						for (int i = 1; i < temp.size(); i++) {
							if (temp[i]->getPosition().distanceToPoint(dot->getPos()) < closest->getPosition().distanceToPoint(dot->getPos())) {
								closest = temp[i];
							}
						}
					}
					this->stored = closest;
				}
			} else {
				if (this->stored->getPosition().distanceToPoint(center) < 5) {
					//this->stored = this->stored->randomConnectedNode();
					Node* tmp = this->stored->attached[0];
					if (this->stored->attached.size() > 1) {
						int i = 0;
						for (Node* node: this->stored->attached) {
							if (node->getPosition().distanceToPoint(dot->getPos()) < tmp->getPosition().distanceToPoint(dot->getPos())) {
								if (this->stored == node) {
									continue;
								}
								tmp = node;
							}
							i++;
						}
					}
					this->stored = tmp;
				}
				if (center.distanceToPoint(dot->getPos()) < 60) {
					this->running = false;
				}
				this->stored->draw();
				float ange = atan2(this->stored->getPosition().y() - center.y(), this->stored->getPosition().x() - center.x());
				*this += Point(3 * cos(ange), 3 * sin(ange));
			}
		}*/
		}
		void vision() {
			/*
			Point center = this->position + Point() + Point(this->width / 2, this->height / 2);
			float ange = atan2(dot->getCenter().y() - center.y(), dot->getCenter().x() - center.x());
			if (std::abs(ange - this->angle) < M_PI_2) {
				bool flag = false;
				for (int i = -20; i <= 20; i++) {
					Point pTemp = Point(center);
					pTemp += Point(300 * cos(this->angle + radians(i)), 300 * sin(this->angle + radians(i)));
					Line temp = Line(center, pTemp);
					Point newTemp = dot->getRect().collideLine(temp);
					if (newTemp.isReal()) {
						if (!flag && center.distanceToPoint(newTemp) > 50) {
							// *this += Point(2 * cos(this->angle + radians(i)), 2 * sin(this->angle + radians(i)));
							flag = !flag;
						}
						Line newTempLine = Line(center, newTemp);
						newTempLine.setColorChannels(COLORS::CYAN);
						newTempLine.drawLine(MegaBase::renderer, MegaBase::offset);
						continue;
					}
					temp.setColorChannels(COLORS::BLACK);
					temp.drawLine(MegaBase::renderer, MegaBase::offset);
				}
			}*/
		}
};
#endif
