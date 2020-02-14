#include "CollideBaseFactory.h"

CollideBase* CollideBaseFactory::CreateBox(Point position, NodeDrawGroup& nodes) {
	Point size(BOX::BOX_WIDTH, BOX::BOX_HEIGHT);
	nodes.addNodeAt(position - size / 2);
	nodes.addNodeAt(position + size + (size / 2));
	nodes.addNodeAt(position + (size.onlyX() * 1.5) - (size.onlyY() / 2));
	nodes.addNodeAt(position + (size.onlyY() * 1.5) - (size.onlyX() / 2));
	return new Box(position);
}
