#pragma once
#ifndef COLLIDE_BASE_FACTORY_H
#define COLLIDE_BASE_FACTORY_H
#include "../primitives/Point.h"
#include "Box.h"
class CollideBaseFactory {
	public:
		static CollideBase* CreateBox(Point position) {
			return new Box(position);
		}
};
#endif
