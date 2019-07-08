#pragma once
#ifndef COLLIDE_BASE_FACTORY_H
#define COLLIDE_BASE_FACTORY_H
#include "../primitives/Point.h"
#include "base/CollideBase.h"
#include "Box.h"
class CollideBaseFactory {
	public:
		static CollideBase* CreateBox(Point position) {
			return new Box(position);
		}
		static CollideBase* CreateBox(Point position, SuperTexture* texture) {
			//std::cout << "Box Creation" << std::endl;
			CollideBase* temp = new Box(position);
			//std::cout << "Box Creation Success" << std::endl;
			//std::cout << temp << std::endl;
			temp->setTexture(texture);
			//std::cout << temp << std::endl;
			return temp;
		}
};
#endif
