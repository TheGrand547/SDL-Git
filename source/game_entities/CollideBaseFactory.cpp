#include "CollideBaseFactory.h"

CollideBase* CollideBaseFactory::CreateBox(Point position, NodeDrawGroup& nodes) {
	Point size(BOX::BOX_WIDTH, BOX::BOX_HEIGHT);
	nodes.addNullNodeAt(position - size / 2);
	nodes.addNullNodeAt(position + size + (size / 2));
	nodes.addNullNodeAt(position + (size.onlyX() * 1.5) - (size.onlyY() / 2));
	nodes.addNullNodeAt(position + (size.onlyY() * 1.5) - (size.onlyX() / 2));
	return new Box(position);
}
