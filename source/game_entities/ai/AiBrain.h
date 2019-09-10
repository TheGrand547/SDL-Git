#pragma once
#ifndef AI_BRAIN_H
#define AI_BRAIN_H
class AiBrain;
#include "AiProng.h"
#include "../base/EnemyBase.h"
#include "../../essential/constants.h"
#include<tuple>
#include<vector>

class AiBrain {
	private:
		// This will get messy af soon
		std::vector<std::tuple<AiProng, bool(*)(double), double(*)(EnemyBase*)>> hahayes; 
	public:
		AiBrain();
		~AiBrain();
		void addProng(AiProng::TYPE prongType, double(*valueFunction)(EnemyBase*), bool(*conditionalFunction)(double b));
		void addTempProng();
		void doBrainThings(EnemyBase* entity);
};
#endif
