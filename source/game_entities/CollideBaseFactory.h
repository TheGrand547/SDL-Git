#pragma once
#ifndef COLLIDE_BASE_FACTORY_H
#define COLLIDE_BASE_FACTORY_H
#include "../primitives/Point.h"
#include "base/CollideBase.h"
#include "Box.h"
#include "NodeDrawGroup.h"

class CollideBaseFactory {
	public:
		static CollideBase* CreateBox(Point position, NodeDrawGroup& nodes);
};
#endif
