#pragma once
#ifndef COLLIDE_BASE_FACTORY_H
#define COLLIDE_BASE_FACTORY_H
#include "../primitives/Point.h"
#include "base/CollideBase.h"
#include "Box.h"
#include "NodeDrawGroup.h"
class CollideBaseFactory {
	public:
		static CollideBase* CreateBox(Point position, NodeDrawGroup& nodes) {
			Point size(BOX::BOX_WIDTH, BOX::BOX_HEIGHT); // Maybe make it a vector for clarity?
			nodes.addNullNodeAt(position - size / 2);
			nodes.addNullNodeAt(position + size + (size / 2));
			nodes.addNullNodeAt(position + (size.onlyX() * 1.5) - (size.onlyY() / 2));
			nodes.addNullNodeAt(position + (size.onlyY() * 1.5) - (size.onlyX() / 2));
			return new Box(position);
		}
};
#endif
