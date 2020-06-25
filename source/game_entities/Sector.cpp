#include "Sector.h"
#include "../essential/MegaBase.h"

Sector::Sector(Rect structure, std::string data) : structure(structure), data(data) {}

Sector::~Sector() {}

bool Sector::contains(Sector* pointer) const {
	for (const std::weak_ptr<Sector>& sector: this->attached) {
		std::shared_ptr<Sector> specific = sector.lock();
		if (specific && specific.get() == pointer) return true;
	} 
	return false;
}

std::string Sector::getData() const {
	return this->data;
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
		if (sector.get() == this || this->contains(sector.get())) continue; // Shouldn't happen but edge cases :D
		for (Line line: lines) {
			if (sector->structure.doesLineCollide(line)) {
				this->attached.push_back(sector);
				Point point = sector->structure.collideLine(line);
				if (!valueInVector(sector->structure.getPoints(), point)) {
					this->pointsOfContact[sector.get()] = point;
				}
			}
		}
	}
}

void Sector::clean(std::vector<std::shared_ptr<Sector>>& others) {
	for (std::shared_ptr<Sector>& sector: others) {
		if (sector->contains(this) && !this->contains(sector.get())) {
			this->attached.push_back(sector);
		}
		if (this->contains(sector.get()) && this->pointsOfContact[sector.get()].isNull()) {
			this->pointsOfContact[sector.get()] = sector->pointsOfContact[this];
		}
		
	}
}

void Sector::draw() {
	this->structure.draw(MegaBase::renderer, *MegaBase::offset);
}
