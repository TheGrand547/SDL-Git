#pragma once
#ifndef SECTOR_H
#define SECTOR_H
class SectorBase;
#include "../essential/MegaBase.h"
#include "../primitives/Line.h"
#include "../primitives/Point.h"
#include "../primitives/Polygon.h"
#include "../primitives/Rect.h"
#include "base/ThingBase.h"
#include<map>
#include<memory>
#include<SDL2/SDL.h>
#include<string>
#include<vector>

class SectorBase {
	public:
		virtual ~SectorBase() {}
		virtual bool contains(SectorBase* pointer) const = 0;
		virtual Polygon& structure() = 0;
		virtual std::map<SectorBase*, Point>& pointsOfContact() = 0;
		virtual std::string getData() const = 0;
		virtual std::vector<std::weak_ptr<SectorBase>>& attached() = 0;
		virtual std::vector<std::weak_ptr<ThingBase>>& getContained() = 0;
		virtual void connectToOthers(std::vector<std::shared_ptr<SectorBase>>& others) = 0;
		virtual void clean(std::vector<std::shared_ptr<SectorBase>>& others) = 0;
		virtual void draw(SDL_Renderer* renderer, Point offset = Point(0, 0)) = 0;
};

template<class T> class Sector : public SectorBase {
	static_assert(std::is_base_of<Polygon, T>::value, "Sector must be templated with a parameter of type polygon.");
	public:
		T representation;
		std::map<SectorBase*, Point> contact;
		std::string data;
		std::vector<std::weak_ptr<SectorBase>> connected;
		std::vector<std::weak_ptr<ThingBase>> containedThings;
	
		Sector(T structure, std::string data = "");
		~Sector();
		bool contains(SectorBase* pointer) const override;
		Polygon& structure() override;
		std::map<SectorBase*, Point>& pointsOfContact() override;
		std::string getData() const override;
		std::vector<std::weak_ptr<SectorBase>>& attached() override;
		std::vector<std::weak_ptr<ThingBase>>& getContained() override;
		void connectToOthers(std::vector<std::shared_ptr<SectorBase>>& others) override;
		void clean(std::vector<std::shared_ptr<SectorBase>>& others) override;
		void draw(SDL_Renderer* renderer, Point offset = Point(0, 0)) override;
};	


template<class T> Sector<T>::Sector(T structure, std::string data) : representation(structure), data(data) {}

template<class T> Sector<T>::~Sector() {}

template<class T> bool Sector<T>::contains(SectorBase* pointer) const {
	for (const std::weak_ptr<SectorBase>& sector: this->connected) {
		std::shared_ptr<SectorBase> specific = sector.lock();
		if (specific && specific.get() == pointer) return true;
	} 
	return false;
}

template<class T> Polygon& Sector<T>::structure() {
	return this->representation;
}

template<class T> std::map<SectorBase*, Point>& Sector<T>::pointsOfContact() {
	return this->contact;
}

template<class T> std::string Sector<T>::getData() const {
	return this->data;
}

template<class T> std::vector<std::weak_ptr<SectorBase>>& Sector<T>::attached() {
	return this->connected;
}

template<class T> std::vector<std::weak_ptr<ThingBase>>& Sector<T>::getContained() {
	return this->containedThings;
}

template<class T> void Sector<T>::connectToOthers(std::vector<std::shared_ptr<SectorBase>>& others) {
	std::vector<Line> lines;
	{
		Point center = this->representation.getCenter();
		for (Line line: this->representation.getLines()) {
			Point direction(line.getUnitVector().rotate90());
			Line positive(center, line.midPoint() + direction * 15);
			Line negative(center, line.midPoint() + direction * -15);
			lines.push_back((positive.getFastMagnitude() > negative.getFastMagnitude()) ? positive: negative);
		}
	}
	for (std::shared_ptr<SectorBase>& sector: others) {
		if (sector.get() == this || this->contains(sector.get())) continue; // Shouldn't happen but edge cases :D
		for (Line line: lines) {
			if (sector->structure().doesLineCollide(line)) {
				this->connected.push_back(sector);
				Point point = sector->structure().collideLine(line);
				if (!valueInVector(sector->structure().getPoints(), point)) {
					this->contact[sector.get()] = point;
				}
			}
		}
	}
}

template<class T> void Sector<T>::clean(std::vector<std::shared_ptr<SectorBase>>& others) {
	for (std::shared_ptr<SectorBase>& sector: others) {
		if (sector->contains(this) && !this->contains(sector.get())) {
			this->connected.push_back(sector);
		}
		if (this->contains(sector.get()) && this->contact[sector.get()].isNull()) {
			this->contact[sector.get()] = sector->pointsOfContact()[this];
		}
		
	}
}

template<class T> void Sector<T>::draw(SDL_Renderer* renderer, Point offset) {
	this->representation.draw(renderer, offset);
}
#endif
