#pragma once
#ifndef EFFECT_ZONE_H
#define EFFECT_ZONE_H
#include "../primitives/Polygon.h"
#include "base/ThingBase.h"
#include<iostream>

// TODO: Probably deprecated
template<typename T> class EffectZone : public ThingBase {
	static_assert(std::is_base_of<Polygon, T>::value, "EffectZone must be templated with a parameter of type polygon.");
	protected:
		T zone;
	public:
		EffectZone(T poly) {std::cout << &poly << std::endl;}
		virtual ~EffectZone() {}
};
#endif
