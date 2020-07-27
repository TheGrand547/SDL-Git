#pragma once
#ifndef EFFECT_H
#define EFFECT_H

#include<memory>

struct Effect {
	virtual ~Effect() {}
	virtual void activate(ThingBase* ptr) = 0;
};

// TODO: Linked list
class EffectList {
	private:
		EffectList* previous, next;
		std::shared_ptr<Effect> effect;
	public:
		EffectList(EffectList* a) : previous(a), next(b);
};


// TEMP THING
class Slow : public effect {
	private:
		double initial;
	public:
		Slow() {}
};
#endif
