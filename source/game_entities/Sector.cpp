#include "Sector.h"

Sector::Sector(Rect structure) : structure(structure) {}

Sector::~Sector() {}

Line Sector::iwannaline() {
	std::vector<Line> tempLines = this->structure.getLines();
	Point center = this->structure.getCenter();
	for (Line line: tempLines) {
		Point direction(line.getUnitVector().rotate90());
		Line positive(center, line.midPoint() + direction * 5);
		Line negative(center, line.midPoint() + direction * -5);
		tempLines.push_back((positive.getFastMagnitude() > negative.getFastMagnitude()) ? positive: negative);
	}
	return tempLines[this->structure.numLines()];
}

void Sector::connectToOthers(std::vector<std::shared_ptr<Sector>>& others) {
	std::vector<Line> lines;
	{
		Point center = this->structure.getCenter();
		for (Line line: this->structure.getLines()) {
			Point direction(line.getUnitVector().rotate90());
			Line positive(center, line.midPoint() + direction * 15);
			Line negative(center, line.midPoint() + direction * -15);
			lines.push_back((positive.getFastMagnitude() > negative.getFastMagnitude()) ? positive: negative);
		}
	}
	for (std::shared_ptr<Sector>& sector: others) {
		for (Line line: lines) {
			if (sector->contains(this) || sector->structure.doesLineCollide(line)) this->attached.push_back(sector);
		}
	}
	std::cout << this->attached.size() << std::endl;
}

bool Sector::contains(Sector* pointer) const {
	for (const std::weak_ptr<Sector>& sector: this->attached) {
		std::shared_ptr<Sector> specific = sector.lock();
		if (specific && specific.get() == pointer) return true;
	} 
	return false;
}
