#include "Sector.h"

SectorBase::~SectorBase() {}

bool SectorBase::contains([[maybe_unused]] AStar::Node<Polygon&>* ptr) const {
	return false;
}
