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
			CollideBase* temp = new Box(position);
			temp->setTexture(texture);
			return temp;
		}
};
#endif
