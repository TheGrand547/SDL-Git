#include "Sector.h"

SectorBase::~SectorBase() {}

bool SectorBase::contains(std::shared_ptr<SectorBase> pointer) const {
	return this->contains(pointer.get());
}
