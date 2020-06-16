#include "Sector.h"

Sector::Sector() {}

Sector::~Sector() {}

std::vector<Sector> Sector::MakeSectors(const std::vector<Line>& collisionLines) {
	std::cout << collisionLines[0] << std::endl;
	return {Sector()};
}
