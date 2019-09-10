#include "AiBrain.h"
#include<iostream>
AiBrain::AiBrain() {}

AiBrain::~AiBrain() {}

void AiBrain::addProng(AiProng::TYPE prongType, double(*valueFunction)(EnemyBase*), bool(*conditionalFunction)(double b)) {
	this->hahayes.push_back(std::make_tuple(AiProng(prongType), conditionalFunction, valueFunction));
}

void AiBrain::addTempProng() {
	this->hahayes.push_back(std::make_tuple(AiProng(AiProng::TYPE::PATHFIND_TO_TARGET), [](double b) -> bool {return true;}, [](EnemyBase* e) -> double {return 1.5;}));	
}

void AiBrain::doBrainThings(EnemyBase* entity) {
	for (std::tuple<AiProng, bool(*)(double), double(*)(EnemyBase*)> hahafun: this->hahayes) {
		if (std::get<1>(hahafun)(std::get<2>(hahafun)(entity))) {
			std::get<0>(hahafun).execute(entity);
			break;
		}
	}
}
